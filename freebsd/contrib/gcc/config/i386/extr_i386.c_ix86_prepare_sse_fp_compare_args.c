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

/* Variables and functions */
#define  EQ 141 
#define  GE 140 
#define  GT 139 
#define  LE 138 
#define  LT 137 
#define  LTGT 136 
#define  NE 135 
#define  ORDERED 134 
#define  UNEQ 133 
#define  UNGE 132 
#define  UNGT 131 
 int UNKNOWN ; 
#define  UNLE 130 
#define  UNLT 129 
#define  UNORDERED 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swap_condition (int) ; 

__attribute__((used)) static enum rtx_code
ix86_prepare_sse_fp_compare_args (rtx dest, enum rtx_code code,
				  rtx *pop0, rtx *pop1)
{
  rtx tmp;

  switch (code)
    {
    case LTGT:
    case UNEQ:
      /* We have no LTGT as an operator.  We could implement it with
	 NE & ORDERED, but this requires an extra temporary.  It's
	 not clear that it's worth it.  */
      return UNKNOWN;

    case LT:
    case LE:
    case UNGT:
    case UNGE:
      /* These are supported directly.  */
      break;

    case EQ:
    case NE:
    case UNORDERED:
    case ORDERED:
      /* For commutative operators, try to canonicalize the destination
	 operand to be first in the comparison - this helps reload to
	 avoid extra moves.  */
      if (!dest || !rtx_equal_p (dest, *pop1))
	break;
      /* FALLTHRU */

    case GE:
    case GT:
    case UNLE:
    case UNLT:
      /* These are not supported directly.  Swap the comparison operands
	 to transform into something that is supported.  */
      tmp = *pop0;
      *pop0 = *pop1;
      *pop1 = tmp;
      code = swap_condition (code);
      break;

    default:
      gcc_unreachable ();
    }

  return code;
}