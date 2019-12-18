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
struct ia64_operand {TYPE_1__* field; } ;
typedef  int ia64_insn ;
struct TYPE_2__ {int bits; } ;

/* Variables and functions */
 char const* ins_immu (struct ia64_operand const*,int,int*) ; 

__attribute__((used)) static const char*
ins_cimmu (const struct ia64_operand *self, ia64_insn value, ia64_insn *code)
{
  ia64_insn mask = (((ia64_insn) 1) << self->field[0].bits) - 1;
  return ins_immu (self, value ^ mask, code);
}