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
typedef  enum comparison_code { ____Placeholder_comparison_code } comparison_code ;

/* Variables and functions */
#define  COMPCODE_EQ 141 
#define  COMPCODE_GE 140 
#define  COMPCODE_GT 139 
#define  COMPCODE_LE 138 
#define  COMPCODE_LT 137 
#define  COMPCODE_LTGT 136 
#define  COMPCODE_NE 135 
#define  COMPCODE_ORD 134 
#define  COMPCODE_UNEQ 133 
#define  COMPCODE_UNGE 132 
#define  COMPCODE_UNGT 131 
#define  COMPCODE_UNLE 130 
#define  COMPCODE_UNLT 129 
#define  COMPCODE_UNORD 128 
 int EQ_EXPR ; 
 int GE_EXPR ; 
 int GT_EXPR ; 
 int LE_EXPR ; 
 int LTGT_EXPR ; 
 int LT_EXPR ; 
 int NE_EXPR ; 
 int ORDERED_EXPR ; 
 int UNEQ_EXPR ; 
 int UNGE_EXPR ; 
 int UNGT_EXPR ; 
 int UNLE_EXPR ; 
 int UNLT_EXPR ; 
 int UNORDERED_EXPR ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static enum tree_code
compcode_to_comparison (enum comparison_code code)
{
  switch (code)
    {
    case COMPCODE_LT:
      return LT_EXPR;
    case COMPCODE_EQ:
      return EQ_EXPR;
    case COMPCODE_LE:
      return LE_EXPR;
    case COMPCODE_GT:
      return GT_EXPR;
    case COMPCODE_NE:
      return NE_EXPR;
    case COMPCODE_GE:
      return GE_EXPR;
    case COMPCODE_ORD:
      return ORDERED_EXPR;
    case COMPCODE_UNORD:
      return UNORDERED_EXPR;
    case COMPCODE_UNLT:
      return UNLT_EXPR;
    case COMPCODE_UNEQ:
      return UNEQ_EXPR;
    case COMPCODE_UNLE:
      return UNLE_EXPR;
    case COMPCODE_UNGT:
      return UNGT_EXPR;
    case COMPCODE_LTGT:
      return LTGT_EXPR;
    case COMPCODE_UNGE:
      return UNGE_EXPR;
    default:
      gcc_unreachable ();
    }
}