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
struct arc_operand_value {int dummy; } ;
struct arc_operand {int bits; int flags; long (* insert ) (long,struct arc_operand const*,int,struct arc_operand_value const*,long,char const**) ;long shift; } ;
typedef  scalar_t__ offsetT ;
typedef  long arc_insn ;

/* Variables and functions */
 int ARC_OPERAND_NEGATIVE ; 
 int ARC_OPERAND_SIGNED ; 
 int ARC_OPERAND_SIGNOPT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (char const*) ; 
 int /*<<< orphan*/  as_warn_value_out_of_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,char*,unsigned int) ; 
 long stub1 (long,struct arc_operand const*,int,struct arc_operand_value const*,long,char const**) ; 

__attribute__((used)) static arc_insn
arc_insert_operand (arc_insn insn,
		    const struct arc_operand *operand,
		    int mods,
		    const struct arc_operand_value *reg,
		    offsetT val,
		    char *file,
		    unsigned int line)
{
  if (operand->bits != 32)
    {
      long min, max;
      offsetT test;

      if ((operand->flags & ARC_OPERAND_SIGNED) != 0)
	{
	  if ((operand->flags & ARC_OPERAND_SIGNOPT) != 0)
	    max = (1 << operand->bits) - 1;
	  else
	    max = (1 << (operand->bits - 1)) - 1;
	  min = - (1 << (operand->bits - 1));
	}
      else
	{
	  max = (1 << operand->bits) - 1;
	  min = 0;
	}

      if ((operand->flags & ARC_OPERAND_NEGATIVE) != 0)
	test = - val;
      else
	test = val;

      if (test < (offsetT) min || test > (offsetT) max)
	as_warn_value_out_of_range (_("operand"), test, (offsetT) min, (offsetT) max, file, line);
    }

  if (operand->insert)
    {
      const char *errmsg;

      errmsg = NULL;
      insn = (*operand->insert) (insn, operand, mods, reg, (long) val, &errmsg);
      if (errmsg != (const char *) NULL)
	as_warn (errmsg);
    }
  else
    insn |= (((long) val & ((1 << operand->bits) - 1))
	     << operand->shift);

  return insn;
}