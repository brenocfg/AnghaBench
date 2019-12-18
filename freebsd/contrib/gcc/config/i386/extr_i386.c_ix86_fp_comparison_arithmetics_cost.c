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
 int /*<<< orphan*/  TARGET_IEEE_FP ; 
#define  UNEQ 133 
#define  UNGE 132 
#define  UNGT 131 
#define  UNLE 130 
#define  UNLT 129 
#define  UNORDERED 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static int
ix86_fp_comparison_arithmetics_cost (enum rtx_code code)
{
  if (!TARGET_IEEE_FP)
    return 4;
  /* The cost of code output by ix86_expand_fp_compare.  */
  switch (code)
    {
    case UNLE:
    case UNLT:
    case LTGT:
    case GT:
    case GE:
    case UNORDERED:
    case ORDERED:
    case UNEQ:
      return 4;
      break;
    case LT:
    case NE:
    case EQ:
    case UNGE:
      return 5;
      break;
    case LE:
    case UNGT:
      return 6;
      break;
    default:
      gcc_unreachable ();
    }
}