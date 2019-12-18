#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ia64_opcode {int ent_index; int /*<<< orphan*/ * dependencies; int /*<<< orphan*/  flags; int /*<<< orphan*/ * operands; int /*<<< orphan*/  mask; int /*<<< orphan*/  opcode; int /*<<< orphan*/  num_outputs; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ia64_insn ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * operands; int /*<<< orphan*/  mask; int /*<<< orphan*/  num_outputs; int /*<<< orphan*/  opcode_type; } ;

/* Variables and functions */
 TYPE_1__* main_table ; 
 int /*<<< orphan*/ * op_dependencies ; 
 scalar_t__ xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct ia64_opcode *
make_ia64_opcode (ia64_insn opcode, const char *name, int place, int depind)
{
  struct ia64_opcode *res =
    (struct ia64_opcode *) xmalloc (sizeof (struct ia64_opcode));
  res->name = xstrdup (name);
  res->type = main_table[place].opcode_type;
  res->num_outputs = main_table[place].num_outputs;
  res->opcode = opcode;
  res->mask = main_table[place].mask;
  res->operands[0] = main_table[place].operands[0];
  res->operands[1] = main_table[place].operands[1];
  res->operands[2] = main_table[place].operands[2];
  res->operands[3] = main_table[place].operands[3];
  res->operands[4] = main_table[place].operands[4];
  res->flags = main_table[place].flags;
  res->ent_index = place;
  res->dependencies = &op_dependencies[depind];
  return res;
}