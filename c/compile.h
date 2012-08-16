#include <stdint.h>
#include "bytecode.h"
#include "opcode.h"

struct inst;
typedef struct inst inst;


typedef struct block {
  inst* first;
  inst* last;
} block;

block gen_noop();
block gen_op_simple(opcode op);
block gen_op_const(opcode op, json_t* constant);
block gen_op_target(opcode op, block target);
block gen_op_var_unbound(opcode op, const char* name);
block gen_op_var_bound(opcode op, block binder);
block gen_op_symbol(opcode op, const char* name);

block gen_subexp(block a);
block gen_both(block a, block b);
block gen_collect(block expr);
block gen_else(block a, block b);


void block_append(block* b, block b2);
block block_join(block a, block b);
block block_bind(block binder, block body);

struct bytecode* block_compile(struct symbol_table*, block);

void block_free(block);