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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  EQ_EXPR 141 
#define  GE_EXPR 140 
#define  GT_EXPR 139 
#define  LE_EXPR 138 
#define  LTGT_EXPR 137 
#define  LT_EXPR 136 
#define  NE_EXPR 135 
#define  ORDERED_EXPR 134 
#define  UNEQ_EXPR 133 
#define  UNGE_EXPR 132 
#define  UNGT_EXPR 131 
#define  UNLE_EXPR 130 
#define  UNLT_EXPR 129 
#define  UNORDERED_EXPR 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

enum tree_code
swap_tree_comparison (enum tree_code code)
{
  switch (code)
    {
    case EQ_EXPR:
    case NE_EXPR:
    case ORDERED_EXPR:
    case UNORDERED_EXPR:
    case LTGT_EXPR:
    case UNEQ_EXPR:
      return code;
    case GT_EXPR:
      return LT_EXPR;
    case GE_EXPR:
      return LE_EXPR;
    case LT_EXPR:
      return GT_EXPR;
    case LE_EXPR:
      return GE_EXPR;
    case UNGT_EXPR:
      return UNLT_EXPR;
    case UNGE_EXPR:
      return UNLE_EXPR;
    case UNLT_EXPR:
      return UNGT_EXPR;
    case UNLE_EXPR:
      return UNGE_EXPR;
    default:
      gcc_unreachable ();
    }
}