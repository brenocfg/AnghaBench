#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct powerpc_operand {int flags; } ;

/* Variables and functions */
 int PPC_OPERAND_NEXT ; 
 int PPC_OPERAND_OPTIONAL ; 
 scalar_t__ operand_value_powerpc (struct powerpc_operand const*,unsigned long,int) ; 
 struct powerpc_operand* powerpc_operands ; 

__attribute__((used)) static int
skip_optional_operands (const unsigned char *opindex,
			unsigned long insn, int dialect)
{
  const struct powerpc_operand *operand;

  for (; *opindex != 0; opindex++)
    {
      operand = &powerpc_operands[*opindex];
      if ((operand->flags & PPC_OPERAND_NEXT) != 0
	  || ((operand->flags & PPC_OPERAND_OPTIONAL) != 0
	      && operand_value_powerpc (operand, insn, dialect) != 0))
	return 0;
    }

  return 1;
}