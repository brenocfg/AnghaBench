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
struct arc_operand_value {size_t type; int flags; int value; } ;
struct arc_operand {char fmt; int shift; } ;
typedef  enum operand { ____Placeholder_operand } operand ;
typedef  int arc_insn ;
struct TYPE_2__ {int shift; } ;

/* Variables and functions */
 int ARC_MOD_AUXREG ; 
 int ARC_REGISTER_READONLY ; 
 int ARC_REGISTER_WRITEONLY ; 
 int ARC_REG_LIMM ; 
 int ARC_REG_SHIMM ; 
 int ARC_REG_SHIMM_UPDATE ; 
 scalar_t__ ARC_SHIMM_CONST_P (long) ; 
 size_t AUXREG ; 
 int I (int) ; 
 size_t LS_BASE ; 
 size_t LS_DEST ; 
 size_t LS_OFFSET ; 
 size_t LS_VALUE ; 
 int OP_LIMM ; 
 int OP_NONE ; 
 int OP_REG ; 
 int OP_SHIMM ; 
 char* _ (char*) ; 
 TYPE_1__* arc_operands ; 
 int /*<<< orphan*/  cond_p ; 
 scalar_t__ flag_p ; 
 int flagshimm_handled_p ; 
 long limm ; 
 int limm_p ; 
 int* ls_operand ; 
 long shimm ; 
 int shimm_p ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static arc_insn
insert_reg (arc_insn insn,
	    const struct arc_operand *operand,
	    int mods,
	    const struct arc_operand_value *reg,
	    long value,
	    const char **errmsg)
{
  static char buf[100];
  enum operand op_type = OP_NONE;

  if (reg == NULL)
    {
      /* We have a constant that also requires a value stored in a register
	 field.  Handle these by updating the register field and saving the
	 value for later handling by either %S (shimm) or %L (limm).  */

      /* Try to use a shimm value before a limm one.  */
      if (ARC_SHIMM_CONST_P (value)
	  /* If we've seen a conditional suffix we have to use a limm.  */
	  && !cond_p
	  /* If we already have a shimm value that is different than ours
	     we have to use a limm.  */
	  && (!shimm_p || shimm == value))
	{
	  int marker;

	  op_type = OP_SHIMM;
	  /* Forget about shimm as dest mlm.  */

	  if ('a' != operand->fmt)
	    {
	      shimm_p = 1;
	      shimm = value;
	      flagshimm_handled_p = 1;
	      marker = flag_p ? ARC_REG_SHIMM_UPDATE : ARC_REG_SHIMM;
	    }
	  else
	    {
	      /* Don't request flag setting on shimm as dest.  */
	      marker = ARC_REG_SHIMM;
	    }
	  insn |= marker << operand->shift;
	  /* insn |= value & 511; - done later.  */
	}
      /* We have to use a limm.  If we've already seen one they must match.  */
      else if (!limm_p || limm == value)
	{
	  op_type = OP_LIMM;
	  limm_p = 1;
	  limm = value;
	  insn |= ARC_REG_LIMM << operand->shift;
	  /* The constant is stored later.  */
	}
      else
	*errmsg = _("unable to fit different valued constants into instruction");
    }
  else
    {
      /* We have to handle both normal and auxiliary registers.  */

      if (reg->type == AUXREG)
	{
	  if (!(mods & ARC_MOD_AUXREG))
	    *errmsg = _("auxiliary register not allowed here");
	  else
	    {
	      if ((insn & I(-1)) == I(2)) /* Check for use validity.  */
		{
		  if (reg->flags & ARC_REGISTER_READONLY)
		    *errmsg = _("attempt to set readonly register");
		}
	      else
		{
		  if (reg->flags & ARC_REGISTER_WRITEONLY)
		    *errmsg = _("attempt to read writeonly register");
		}
	      insn |= ARC_REG_SHIMM << operand->shift;
	      insn |= reg->value << arc_operands[reg->type].shift;
	    }
	}
      else
	{
	  /* check for use validity.  */
	  if ('a' == operand->fmt || ((insn & I(-1)) < I(2)))
	    {
	      if (reg->flags & ARC_REGISTER_READONLY)
		*errmsg = _("attempt to set readonly register");
	    }
	  if ('a' != operand->fmt)
	    {
	      if (reg->flags & ARC_REGISTER_WRITEONLY)
		*errmsg = _("attempt to read writeonly register");
	    }
	  /* We should never get an invalid register number here.  */
	  if ((unsigned int) reg->value > 60)
	    {
	      sprintf (buf, _("invalid register number `%d'"), reg->value);
	      *errmsg = buf;
	    }
	  insn |= reg->value << operand->shift;
	  op_type = OP_REG;
	}
    }

  switch (operand->fmt)
    {
    case 'a':
      ls_operand[LS_DEST] = op_type;
      break;
    case 's':
      ls_operand[LS_BASE] = op_type;
      break;
    case 'c':
      if ((insn & I(-1)) == I(2))
	ls_operand[LS_VALUE] = op_type;
      else
	ls_operand[LS_OFFSET] = op_type;
      break;
    case 'o': case 'O':
      ls_operand[LS_OFFSET] = op_type;
      break;
    }

  return insn;
}