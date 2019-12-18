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
 int COMPCODE_EQ ; 
 int COMPCODE_GE ; 
 int COMPCODE_GT ; 
 int COMPCODE_LE ; 
 int COMPCODE_LT ; 
 int COMPCODE_LTGT ; 
 int COMPCODE_NE ; 
 int COMPCODE_ORD ; 
 int COMPCODE_UNEQ ; 
 int COMPCODE_UNGE ; 
 int COMPCODE_UNGT ; 
 int COMPCODE_UNLE ; 
 int COMPCODE_UNLT ; 
 int COMPCODE_UNORD ; 
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

__attribute__((used)) static enum comparison_code
comparison_to_compcode (enum tree_code code)
{
  switch (code)
    {
    case LT_EXPR:
      return COMPCODE_LT;
    case EQ_EXPR:
      return COMPCODE_EQ;
    case LE_EXPR:
      return COMPCODE_LE;
    case GT_EXPR:
      return COMPCODE_GT;
    case NE_EXPR:
      return COMPCODE_NE;
    case GE_EXPR:
      return COMPCODE_GE;
    case ORDERED_EXPR:
      return COMPCODE_ORD;
    case UNORDERED_EXPR:
      return COMPCODE_UNORD;
    case UNLT_EXPR:
      return COMPCODE_UNLT;
    case UNEQ_EXPR:
      return COMPCODE_UNEQ;
    case UNLE_EXPR:
      return COMPCODE_UNLE;
    case UNGT_EXPR:
      return COMPCODE_UNGT;
    case LTGT_EXPR:
      return COMPCODE_LTGT;
    case UNGE_EXPR:
      return COMPCODE_UNGE;
    default:
      gcc_unreachable ();
    }
}