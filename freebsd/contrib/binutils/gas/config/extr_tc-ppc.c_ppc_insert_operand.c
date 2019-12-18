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
struct powerpc_operand {long bitm; int flags; unsigned long (* insert ) (unsigned long,long,int /*<<< orphan*/ ,char const**) ;long shift; } ;
typedef  long offsetT ;

/* Variables and functions */
 int PPC_OPERAND_NEGATIVE ; 
 int PPC_OPERAND_PLUS1 ; 
 int PPC_OPERAND_SIGNED ; 
 int PPC_OPERAND_SIGNOPT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad_value_out_of_range (int /*<<< orphan*/ ,long,long,long,char*,unsigned int) ; 
 int /*<<< orphan*/  as_bad_where (char*,unsigned int,char*,char const*) ; 
 int /*<<< orphan*/  ppc_cpu ; 
 unsigned long stub1 (unsigned long,long,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static unsigned long
ppc_insert_operand (unsigned long insn,
		    const struct powerpc_operand *operand,
		    offsetT val,
		    char *file,
		    unsigned int line)
{
  long min, max, right;

  max = operand->bitm;
  right = max & -max;
  min = 0;

  if ((operand->flags & PPC_OPERAND_SIGNED) != 0)
    {
      if ((operand->flags & PPC_OPERAND_SIGNOPT) == 0)
	max = (max >> 1) & -right;
      min = ~max & -right;
    }

  if ((operand->flags & PPC_OPERAND_PLUS1) != 0)
    max++;

  if ((operand->flags & PPC_OPERAND_NEGATIVE) != 0)
    {
      long tmp = min;
      min = -max;
      max = -tmp;
    }

  if (min <= max)
    {
      /* Some people write constants with the sign extension done by
	 hand but only up to 32 bits.  This shouldn't really be valid,
	 but, to permit this code to assemble on a 64-bit host, we
	 sign extend the 32-bit value to 64 bits if so doing makes the
	 value valid.  */
      if (val > max
	  && (offsetT) (val - 0x80000000 - 0x80000000) >= min
	  && (offsetT) (val - 0x80000000 - 0x80000000) <= max
	  && ((val - 0x80000000 - 0x80000000) & (right - 1)) == 0)
	val = val - 0x80000000 - 0x80000000;

      /* Similarly, people write expressions like ~(1<<15), and expect
	 this to be OK for a 32-bit unsigned value.  */
      else if (val < min
	       && (offsetT) (val + 0x80000000 + 0x80000000) >= min
	       && (offsetT) (val + 0x80000000 + 0x80000000) <= max
	       && ((val + 0x80000000 + 0x80000000) & (right - 1)) == 0)
	val = val + 0x80000000 + 0x80000000;

      else if (val < min
	       || val > max
	       || (val & (right - 1)) != 0)
	as_bad_value_out_of_range (_("operand"), val, min, max, file, line);
    }

  if (operand->insert)
    {
      const char *errmsg;

      errmsg = NULL;
      insn = (*operand->insert) (insn, (long) val, ppc_cpu, &errmsg);
      if (errmsg != (const char *) NULL)
	as_bad_where (file, line, "%s", errmsg);
    }
  else
    insn |= ((long) val & operand->bitm) << operand->shift;

  return insn;
}