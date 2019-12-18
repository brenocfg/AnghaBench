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
struct TYPE_2__ {int shift; } ;
typedef  int BFD_HOST_64_BIT ;

/* Variables and functions */

__attribute__((used)) static const char*
ext_inc3 (const struct ia64_operand *self, ia64_insn code, ia64_insn *valuep)
{
  BFD_HOST_64_BIT val;
  int negate;

  val = (code >> self->field[0].shift) & 0x7;
  negate = val & 0x4;
  switch (val & 0x3)
    {
    case 0: val = 16; break;
    case 1: val =  8; break;
    case 2: val =  4; break;
    case 3: val =  1; break;
    }
  if (negate)
    val = -val;

  *valuep = val;
  return 0;
}