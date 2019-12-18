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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int madbr; int maebr; int mhi; int mh; int ms; int mghi; int msgf; int msg; int m; int ml; int mult_df; int mxbr; int dlgr; int dlr; int dsgfr; int dr; int dsgr; int debr; int der; int ddbr; int ddr; int dxbr; int dxr; int sqebr; int sqdbr; int sqxbr; } ;

/* Variables and functions */
#define  AND 159 
#define  ASHIFT 158 
#define  ASHIFTRT 157 
#define  COMPARE 156 
#define  CONST 155 
#define  CONST_DOUBLE 154 
#define  CONST_INT 153 
 int /*<<< orphan*/  CONST_OK_FOR_K (int /*<<< orphan*/ ) ; 
 int COSTS_N_INSNS (int) ; 
#define  DFmode 152 
#define  DIV 151 
#define  DImode 150 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  IOR 149 
#define  LABEL_REF 148 
#define  LSHIFTRT 147 
#define  MEM 146 
#define  MINUS 145 
#define  MOD 144 
#define  MULT 143 
#define  NEG 142 
#define  NOT 141 
#define  PLUS 140 
#define  ROTATE 139 
#define  ROTATERT 138 
#define  SFmode 137 
#define  SIGN_EXTEND 136 
#define  SImode 135 
#define  SQRT 134 
#define  SYMBOL_REF 133 
 int /*<<< orphan*/  TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_CPU_ZARCH ; 
 int /*<<< orphan*/  TARGET_FUSED_MADD ; 
 int /*<<< orphan*/  TARGET_HARD_FLOAT ; 
 int /*<<< orphan*/  TARGET_IEEE_FLOAT ; 
#define  TFmode 132 
 int TImode ; 
#define  UDIV 131 
#define  UMOD 130 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
#define  XOR 129 
#define  ZERO_EXTEND 128 
 int /*<<< orphan*/  memory_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  register_operand (int /*<<< orphan*/ ,int) ; 
 int rtx_cost (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* s390_cost ; 
 int /*<<< orphan*/  s390_tm_ccmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
s390_rtx_costs (rtx x, int code, int outer_code, int *total)
{
  switch (code)
    {
    case CONST:
    case CONST_INT:
    case LABEL_REF:
    case SYMBOL_REF:
    case CONST_DOUBLE:
    case MEM:
      *total = 0;
      return true;

    case ASHIFT:
    case ASHIFTRT:
    case LSHIFTRT:
    case ROTATE:
    case ROTATERT:
    case AND:
    case IOR:
    case XOR:
    case NEG:
    case NOT:
      *total = COSTS_N_INSNS (1);
      return false;

    case PLUS:
    case MINUS:
      /* Check for multiply and add.  */
      if ((GET_MODE (x) == DFmode || GET_MODE (x) == SFmode)
	  && GET_CODE (XEXP (x, 0)) == MULT
	  && TARGET_HARD_FLOAT && TARGET_IEEE_FLOAT && TARGET_FUSED_MADD)
	{
	  /* This is the multiply and add case.  */
	  if (GET_MODE (x) == DFmode)
	    *total = s390_cost->madbr;
	  else
	    *total = s390_cost->maebr;
	  *total += rtx_cost (XEXP (XEXP (x, 0), 0), MULT) 
	    + rtx_cost (XEXP (XEXP (x, 0), 1), MULT) 
	    + rtx_cost (XEXP (x, 1), code);
	  return true;  /* Do not do an additional recursive descent.  */
	}
      *total = COSTS_N_INSNS (1);
      return false;

    case MULT:      
      switch (GET_MODE (x))
	{
	case SImode:
	  {
	    rtx left = XEXP (x, 0);
	    rtx right = XEXP (x, 1);
	    if (GET_CODE (right) == CONST_INT
		&& CONST_OK_FOR_K (INTVAL (right)))
	      *total = s390_cost->mhi;
	    else if (GET_CODE (left) == SIGN_EXTEND)
	      *total = s390_cost->mh;
	    else
	      *total = s390_cost->ms;  /* msr, ms, msy */
	    break;
	  }
	case DImode:
	  {
	    rtx left = XEXP (x, 0);
	    rtx right = XEXP (x, 1);
	    if (TARGET_64BIT)
	      {
		if (GET_CODE (right) == CONST_INT
		    && CONST_OK_FOR_K (INTVAL (right)))
		  *total = s390_cost->mghi;
		else if (GET_CODE (left) == SIGN_EXTEND)
		  *total = s390_cost->msgf;
		else
		  *total = s390_cost->msg;  /* msgr, msg */
	      }
	    else /* TARGET_31BIT */
	      {
		if (GET_CODE (left) == SIGN_EXTEND
		    && GET_CODE (right) == SIGN_EXTEND)
		  /* mulsidi case: mr, m */
		  *total = s390_cost->m;
		else if (GET_CODE (left) == ZERO_EXTEND
			 && GET_CODE (right) == ZERO_EXTEND
			 && TARGET_CPU_ZARCH)
		  /* umulsidi case: ml, mlr */
		  *total = s390_cost->ml;
		else
		  /* Complex calculation is required.  */
		  *total = COSTS_N_INSNS (40);
	      }
	    break;
	  }
	case SFmode:
	case DFmode:
	  *total = s390_cost->mult_df;
	  break;
	case TFmode:
	  *total = s390_cost->mxbr;
	  break;
	default:
	  return false;
	}
      return false;

    case UDIV:
    case UMOD:
      if (GET_MODE (x) == TImode) 	       /* 128 bit division */
	*total = s390_cost->dlgr;
      else if (GET_MODE (x) == DImode)
	{
	  rtx right = XEXP (x, 1);
	  if (GET_CODE (right) == ZERO_EXTEND) /* 64 by 32 bit division */
	    *total = s390_cost->dlr;
	  else 	                               /* 64 by 64 bit division */
	    *total = s390_cost->dlgr;
	}
      else if (GET_MODE (x) == SImode)         /* 32 bit division */
	*total = s390_cost->dlr;
      return false;

    case DIV:
    case MOD:
      if (GET_MODE (x) == DImode)
	{
	  rtx right = XEXP (x, 1);
	  if (GET_CODE (right) == ZERO_EXTEND) /* 64 by 32 bit division */
	    if (TARGET_64BIT)
	      *total = s390_cost->dsgfr;
	    else
	      *total = s390_cost->dr;
	  else 	                               /* 64 by 64 bit division */
	    *total = s390_cost->dsgr;
	}
      else if (GET_MODE (x) == SImode)         /* 32 bit division */
	*total = s390_cost->dlr;
      else if (GET_MODE (x) == SFmode)
	{
	  if (TARGET_IEEE_FLOAT)
	    *total = s390_cost->debr;
	  else /* TARGET_IBM_FLOAT */
	    *total = s390_cost->der;
	}
      else if (GET_MODE (x) == DFmode)
	{
	  if (TARGET_IEEE_FLOAT)
	    *total = s390_cost->ddbr;
	  else /* TARGET_IBM_FLOAT */
	    *total = s390_cost->ddr;
	}
      else if (GET_MODE (x) == TFmode)
	{
	  if (TARGET_IEEE_FLOAT)
	    *total = s390_cost->dxbr;
	  else /* TARGET_IBM_FLOAT */
	    *total = s390_cost->dxr;
	}
      return false;

    case SQRT:
      if (GET_MODE (x) == SFmode)
	*total = s390_cost->sqebr;
      else if (GET_MODE (x) == DFmode)
	*total = s390_cost->sqdbr;
      else /* TFmode */
	*total = s390_cost->sqxbr;
      return false;

    case SIGN_EXTEND:
    case ZERO_EXTEND:
      if (outer_code == MULT || outer_code == DIV || outer_code == MOD
	  || outer_code == PLUS || outer_code == MINUS
	  || outer_code == COMPARE)
	*total = 0;
      return false;

    case COMPARE:
      *total = COSTS_N_INSNS (1);
      if (GET_CODE (XEXP (x, 0)) == AND
	  && GET_CODE (XEXP (x, 1)) == CONST_INT
	  && GET_CODE (XEXP (XEXP (x, 0), 1)) == CONST_INT)
	{
	  rtx op0 = XEXP (XEXP (x, 0), 0);
	  rtx op1 = XEXP (XEXP (x, 0), 1);
	  rtx op2 = XEXP (x, 1);

	  if (memory_operand (op0, GET_MODE (op0))
	      && s390_tm_ccmode (op1, op2, 0) != VOIDmode)
	    return true;
	  if (register_operand (op0, GET_MODE (op0))
	      && s390_tm_ccmode (op1, op2, 1) != VOIDmode)
	    return true;
	}
      return false;

    default:
      return false;
    }
}