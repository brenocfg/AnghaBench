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
typedef  scalar_t__ rtx ;
typedef  enum reload_type { ____Placeholder_reload_type } reload_type ;
struct TYPE_2__ {scalar_t__ reg_rtx; scalar_t__ in; scalar_t__ out; int when_needed; int opnum; scalar_t__ out_reg; } ;

/* Variables and functions */
 size_t GET_MODE (scalar_t__) ; 
 int MAX_RECOG_OPERANDS ; 
 scalar_t__ NULL_RTX ; 
 size_t REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
#define  RELOAD_FOR_INPADDR_ADDRESS 138 
#define  RELOAD_FOR_INPUT 137 
#define  RELOAD_FOR_INPUT_ADDRESS 136 
#define  RELOAD_FOR_INSN 135 
#define  RELOAD_FOR_OPADDR_ADDR 134 
#define  RELOAD_FOR_OPERAND_ADDRESS 133 
#define  RELOAD_FOR_OTHER_ADDRESS 132 
#define  RELOAD_FOR_OUTADDR_ADDRESS 131 
#define  RELOAD_FOR_OUTPUT 130 
#define  RELOAD_FOR_OUTPUT_ADDRESS 129 
#define  RELOAD_OTHER 128 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ earlyclobber_operand_p (scalar_t__) ; 
 unsigned int** hard_regno_nregs ; 
 int n_reloads ; 
 int /*<<< orphan*/  reload_reg_unavailable ; 
 TYPE_1__* rld ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 int true_regnum (scalar_t__) ; 

__attribute__((used)) static int
reload_reg_free_for_value_p (int start_regno, int regno, int opnum,
			     enum reload_type type, rtx value, rtx out,
			     int reloadnum, int ignore_address_reloads)
{
  int time1;
  /* Set if we see an input reload that must not share its reload register
     with any new earlyclobber, but might otherwise share the reload
     register with an output or input-output reload.  */
  int check_earlyclobber = 0;
  int i;
  int copy = 0;

  if (TEST_HARD_REG_BIT (reload_reg_unavailable, regno))
    return 0;

  if (out == const0_rtx)
    {
      copy = 1;
      out = NULL_RTX;
    }

  /* We use some pseudo 'time' value to check if the lifetimes of the
     new register use would overlap with the one of a previous reload
     that is not read-only or uses a different value.
     The 'time' used doesn't have to be linear in any shape or form, just
     monotonic.
     Some reload types use different 'buckets' for each operand.
     So there are MAX_RECOG_OPERANDS different time values for each
     such reload type.
     We compute TIME1 as the time when the register for the prospective
     new reload ceases to be live, and TIME2 for each existing
     reload as the time when that the reload register of that reload
     becomes live.
     Where there is little to be gained by exact lifetime calculations,
     we just make conservative assumptions, i.e. a longer lifetime;
     this is done in the 'default:' cases.  */
  switch (type)
    {
    case RELOAD_FOR_OTHER_ADDRESS:
      /* RELOAD_FOR_OTHER_ADDRESS conflicts with RELOAD_OTHER reloads.  */
      time1 = copy ? 0 : 1;
      break;
    case RELOAD_OTHER:
      time1 = copy ? 1 : MAX_RECOG_OPERANDS * 5 + 5;
      break;
      /* For each input, we may have a sequence of RELOAD_FOR_INPADDR_ADDRESS,
	 RELOAD_FOR_INPUT_ADDRESS and RELOAD_FOR_INPUT.  By adding 0 / 1 / 2 ,
	 respectively, to the time values for these, we get distinct time
	 values.  To get distinct time values for each operand, we have to
	 multiply opnum by at least three.  We round that up to four because
	 multiply by four is often cheaper.  */
    case RELOAD_FOR_INPADDR_ADDRESS:
      time1 = opnum * 4 + 2;
      break;
    case RELOAD_FOR_INPUT_ADDRESS:
      time1 = opnum * 4 + 3;
      break;
    case RELOAD_FOR_INPUT:
      /* All RELOAD_FOR_INPUT reloads remain live till the instruction
	 executes (inclusive).  */
      time1 = copy ? opnum * 4 + 4 : MAX_RECOG_OPERANDS * 4 + 3;
      break;
    case RELOAD_FOR_OPADDR_ADDR:
      /* opnum * 4 + 4
	 <= (MAX_RECOG_OPERANDS - 1) * 4 + 4 == MAX_RECOG_OPERANDS * 4 */
      time1 = MAX_RECOG_OPERANDS * 4 + 1;
      break;
    case RELOAD_FOR_OPERAND_ADDRESS:
      /* RELOAD_FOR_OPERAND_ADDRESS reloads are live even while the insn
	 is executed.  */
      time1 = copy ? MAX_RECOG_OPERANDS * 4 + 2 : MAX_RECOG_OPERANDS * 4 + 3;
      break;
    case RELOAD_FOR_OUTADDR_ADDRESS:
      time1 = MAX_RECOG_OPERANDS * 4 + 4 + opnum;
      break;
    case RELOAD_FOR_OUTPUT_ADDRESS:
      time1 = MAX_RECOG_OPERANDS * 4 + 5 + opnum;
      break;
    default:
      time1 = MAX_RECOG_OPERANDS * 5 + 5;
    }

  for (i = 0; i < n_reloads; i++)
    {
      rtx reg = rld[i].reg_rtx;
      if (reg && REG_P (reg)
	  && ((unsigned) regno - true_regnum (reg)
	      <= hard_regno_nregs[REGNO (reg)][GET_MODE (reg)] - (unsigned) 1)
	  && i != reloadnum)
	{
	  rtx other_input = rld[i].in;

	  /* If the other reload loads the same input value, that
	     will not cause a conflict only if it's loading it into
	     the same register.  */
	  if (true_regnum (reg) != start_regno)
	    other_input = NULL_RTX;
	  if (! other_input || ! rtx_equal_p (other_input, value)
	      || rld[i].out || out)
	    {
	      int time2;
	      switch (rld[i].when_needed)
		{
		case RELOAD_FOR_OTHER_ADDRESS:
		  time2 = 0;
		  break;
		case RELOAD_FOR_INPADDR_ADDRESS:
		  /* find_reloads makes sure that a
		     RELOAD_FOR_{INP,OP,OUT}ADDR_ADDRESS reload is only used
		     by at most one - the first -
		     RELOAD_FOR_{INPUT,OPERAND,OUTPUT}_ADDRESS .  If the
		     address reload is inherited, the address address reload
		     goes away, so we can ignore this conflict.  */
		  if (type == RELOAD_FOR_INPUT_ADDRESS && reloadnum == i + 1
		      && ignore_address_reloads
		      /* Unless the RELOAD_FOR_INPUT is an auto_inc expression.
			 Then the address address is still needed to store
			 back the new address.  */
		      && ! rld[reloadnum].out)
		    continue;
		  /* Likewise, if a RELOAD_FOR_INPUT can inherit a value, its
		     RELOAD_FOR_INPUT_ADDRESS / RELOAD_FOR_INPADDR_ADDRESS
		     reloads go away.  */
		  if (type == RELOAD_FOR_INPUT && opnum == rld[i].opnum
		      && ignore_address_reloads
		      /* Unless we are reloading an auto_inc expression.  */
		      && ! rld[reloadnum].out)
		    continue;
		  time2 = rld[i].opnum * 4 + 2;
		  break;
		case RELOAD_FOR_INPUT_ADDRESS:
		  if (type == RELOAD_FOR_INPUT && opnum == rld[i].opnum
		      && ignore_address_reloads
		      && ! rld[reloadnum].out)
		    continue;
		  time2 = rld[i].opnum * 4 + 3;
		  break;
		case RELOAD_FOR_INPUT:
		  time2 = rld[i].opnum * 4 + 4;
		  check_earlyclobber = 1;
		  break;
		  /* rld[i].opnum * 4 + 4 <= (MAX_RECOG_OPERAND - 1) * 4 + 4
		     == MAX_RECOG_OPERAND * 4  */
		case RELOAD_FOR_OPADDR_ADDR:
		  if (type == RELOAD_FOR_OPERAND_ADDRESS && reloadnum == i + 1
		      && ignore_address_reloads
		      && ! rld[reloadnum].out)
		    continue;
		  time2 = MAX_RECOG_OPERANDS * 4 + 1;
		  break;
		case RELOAD_FOR_OPERAND_ADDRESS:
		  time2 = MAX_RECOG_OPERANDS * 4 + 2;
		  check_earlyclobber = 1;
		  break;
		case RELOAD_FOR_INSN:
		  time2 = MAX_RECOG_OPERANDS * 4 + 3;
		  break;
		case RELOAD_FOR_OUTPUT:
		  /* All RELOAD_FOR_OUTPUT reloads become live just after the
		     instruction is executed.  */
		  time2 = MAX_RECOG_OPERANDS * 4 + 4;
		  break;
		  /* The first RELOAD_FOR_OUTADDR_ADDRESS reload conflicts with
		     the RELOAD_FOR_OUTPUT reloads, so assign it the same time
		     value.  */
		case RELOAD_FOR_OUTADDR_ADDRESS:
		  if (type == RELOAD_FOR_OUTPUT_ADDRESS && reloadnum == i + 1
		      && ignore_address_reloads
		      && ! rld[reloadnum].out)
		    continue;
		  time2 = MAX_RECOG_OPERANDS * 4 + 4 + rld[i].opnum;
		  break;
		case RELOAD_FOR_OUTPUT_ADDRESS:
		  time2 = MAX_RECOG_OPERANDS * 4 + 5 + rld[i].opnum;
		  break;
		case RELOAD_OTHER:
		  /* If there is no conflict in the input part, handle this
		     like an output reload.  */
		  if (! rld[i].in || rtx_equal_p (other_input, value))
		    {
		      time2 = MAX_RECOG_OPERANDS * 4 + 4;
		      /* Earlyclobbered outputs must conflict with inputs.  */
		      if (earlyclobber_operand_p (rld[i].out))
			time2 = MAX_RECOG_OPERANDS * 4 + 3;

		      break;
		    }
		  time2 = 1;
		  /* RELOAD_OTHER might be live beyond instruction execution,
		     but this is not obvious when we set time2 = 1.  So check
		     here if there might be a problem with the new reload
		     clobbering the register used by the RELOAD_OTHER.  */
		  if (out)
		    return 0;
		  break;
		default:
		  return 0;
		}
	      if ((time1 >= time2
		   && (! rld[i].in || rld[i].out
		       || ! rtx_equal_p (other_input, value)))
		  || (out && rld[reloadnum].out_reg
		      && time2 >= MAX_RECOG_OPERANDS * 4 + 3))
		return 0;
	    }
	}
    }

  /* Earlyclobbered outputs must conflict with inputs.  */
  if (check_earlyclobber && out && earlyclobber_operand_p (out))
    return 0;

  return 1;
}