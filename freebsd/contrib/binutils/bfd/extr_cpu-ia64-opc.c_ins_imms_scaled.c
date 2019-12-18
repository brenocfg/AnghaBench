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
struct TYPE_2__ {int bits; int shift; } ;
typedef  int BFD_HOST_64_BIT ;

/* Variables and functions */
 int NELEMS (TYPE_1__*) ; 

__attribute__((used)) static const char*
ins_imms_scaled (const struct ia64_operand *self, ia64_insn value,
		 ia64_insn *code, int scale)
{
  BFD_HOST_64_BIT svalue = value, sign_bit = 0;
  ia64_insn new = 0;
  int i;

  svalue >>= scale;

  for (i = 0; i < NELEMS (self->field) && self->field[i].bits; ++i)
    {
      new |= ((svalue & ((((ia64_insn) 1) << self->field[i].bits) - 1))
	      << self->field[i].shift);
      sign_bit = (svalue >> (self->field[i].bits - 1)) & 1;
      svalue >>= self->field[i].bits;
    }
  if ((!sign_bit && svalue != 0) || (sign_bit && svalue != -1))
    return "integer operand out of range";

  *code |= new;
  return 0;
}