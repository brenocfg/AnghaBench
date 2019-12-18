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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int CCGCmode ; 
 int CCGOCmode ; 
 int CCNOmode ; 
 int CCZmode ; 
 int CCmode ; 
#define  EQ 138 
#define  GE 137 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
#define  GEU 136 
#define  GT 135 
#define  GTU 134 
#define  LE 133 
#define  LEU 132 
#define  LT 131 
#define  LTU 130 
#define  NE 129 
 scalar_t__ SCALAR_FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
#define  USE 128 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int ix86_fp_compare_mode (int) ; 

enum machine_mode
ix86_cc_mode (enum rtx_code code, rtx op0, rtx op1)
{
  if (SCALAR_FLOAT_MODE_P (GET_MODE (op0)))
    return ix86_fp_compare_mode (code);
  switch (code)
    {
      /* Only zero flag is needed.  */
    case EQ:			/* ZF=0 */
    case NE:			/* ZF!=0 */
      return CCZmode;
      /* Codes needing carry flag.  */
    case GEU:			/* CF=0 */
    case GTU:			/* CF=0 & ZF=0 */
    case LTU:			/* CF=1 */
    case LEU:			/* CF=1 | ZF=1 */
      return CCmode;
      /* Codes possibly doable only with sign flag when
         comparing against zero.  */
    case GE:			/* SF=OF   or   SF=0 */
    case LT:			/* SF<>OF  or   SF=1 */
      if (op1 == const0_rtx)
	return CCGOCmode;
      else
	/* For other cases Carry flag is not required.  */
	return CCGCmode;
      /* Codes doable only with sign flag when comparing
         against zero, but we miss jump instruction for it
         so we need to use relational tests against overflow
         that thus needs to be zero.  */
    case GT:			/* ZF=0 & SF=OF */
    case LE:			/* ZF=1 | SF<>OF */
      if (op1 == const0_rtx)
	return CCNOmode;
      else
	return CCGCmode;
      /* strcmp pattern do (use flags) and combine may ask us for proper
	 mode.  */
    case USE:
      return CCmode;
    default:
      gcc_unreachable ();
    }
}