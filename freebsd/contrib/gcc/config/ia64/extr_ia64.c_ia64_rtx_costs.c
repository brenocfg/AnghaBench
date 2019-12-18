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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  ASHIFT 143 
#define  ASHIFTRT 142 
#define  CONST 141 
#define  CONST_DOUBLE 140 
#define  CONST_INT 139 
 int /*<<< orphan*/  CONST_OK_FOR_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_OK_FOR_J (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_OK_FOR_K (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_OK_FOR_L (int /*<<< orphan*/ ) ; 
 int COSTS_N_INSNS (int) ; 
#define  DIV 138 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 137 
#define  LSHIFTRT 136 
#define  MINUS 135 
#define  MOD 134 
#define  MULT 133 
#define  PLUS 132 
#define  SET 131 
#define  SYMBOL_REF 130 
#define  UDIV 129 
#define  UMOD 128 

__attribute__((used)) static bool
ia64_rtx_costs (rtx x, int code, int outer_code, int *total)
{
  switch (code)
    {
    case CONST_INT:
      switch (outer_code)
        {
        case SET:
	  *total = CONST_OK_FOR_J (INTVAL (x)) ? 0 : COSTS_N_INSNS (1);
	  return true;
        case PLUS:
	  if (CONST_OK_FOR_I (INTVAL (x)))
	    *total = 0;
	  else if (CONST_OK_FOR_J (INTVAL (x)))
	    *total = 1;
	  else
	    *total = COSTS_N_INSNS (1);
	  return true;
        default:
	  if (CONST_OK_FOR_K (INTVAL (x)) || CONST_OK_FOR_L (INTVAL (x)))
	    *total = 0;
	  else
	    *total = COSTS_N_INSNS (1);
	  return true;
	}

    case CONST_DOUBLE:
      *total = COSTS_N_INSNS (1);
      return true;

    case CONST:
    case SYMBOL_REF:
    case LABEL_REF:
      *total = COSTS_N_INSNS (3);
      return true;

    case MULT:
      /* For multiplies wider than HImode, we have to go to the FPU,
         which normally involves copies.  Plus there's the latency
         of the multiply itself, and the latency of the instructions to
         transfer integer regs to FP regs.  */
      /* ??? Check for FP mode.  */
      if (GET_MODE_SIZE (GET_MODE (x)) > 2)
        *total = COSTS_N_INSNS (10);
      else
	*total = COSTS_N_INSNS (2);
      return true;

    case PLUS:
    case MINUS:
    case ASHIFT:
    case ASHIFTRT:
    case LSHIFTRT:
      *total = COSTS_N_INSNS (1);
      return true;

    case DIV:
    case UDIV:
    case MOD:
    case UMOD:
      /* We make divide expensive, so that divide-by-constant will be
         optimized to a multiply.  */
      *total = COSTS_N_INSNS (60);
      return true;

    default:
      return false;
    }
}