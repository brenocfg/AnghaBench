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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int EQ ; 
#define  EQ_EXPR 141 
 int GE ; 
 int GEU ; 
#define  GE_EXPR 140 
 int GT ; 
 int GTU ; 
#define  GT_EXPR 139 
 int LE ; 
 int LEU ; 
#define  LE_EXPR 138 
 int LT ; 
 int LTGT ; 
#define  LTGT_EXPR 137 
 int LTU ; 
#define  LT_EXPR 136 
 int NE ; 
#define  NE_EXPR 135 
 int ORDERED ; 
#define  ORDERED_EXPR 134 
 int UNEQ ; 
#define  UNEQ_EXPR 133 
 int UNGE ; 
#define  UNGE_EXPR 132 
 int UNGT ; 
#define  UNGT_EXPR 131 
 int UNLE ; 
#define  UNLE_EXPR 130 
 int UNLT ; 
#define  UNLT_EXPR 129 
 int UNORDERED ; 
#define  UNORDERED_EXPR 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static enum rtx_code
get_rtx_code (enum tree_code tcode, bool unsignedp)
{
  enum rtx_code code;
  switch (tcode)
    {
    case EQ_EXPR:
      code = EQ;
      break;
    case NE_EXPR:
      code = NE;
      break;
    case LT_EXPR:
      code = unsignedp ? LTU : LT;
      break;
    case LE_EXPR:
      code = unsignedp ? LEU : LE;
      break;
    case GT_EXPR:
      code = unsignedp ? GTU : GT;
      break;
    case GE_EXPR:
      code = unsignedp ? GEU : GE;
      break;

    case UNORDERED_EXPR:
      code = UNORDERED;
      break;
    case ORDERED_EXPR:
      code = ORDERED;
      break;
    case UNLT_EXPR:
      code = UNLT;
      break;
    case UNLE_EXPR:
      code = UNLE;
      break;
    case UNGT_EXPR:
      code = UNGT;
      break;
    case UNGE_EXPR:
      code = UNGE;
      break;
    case UNEQ_EXPR:
      code = UNEQ;
      break;
    case LTGT_EXPR:
      code = LTGT;
      break;

    default:
      gcc_unreachable ();
    }
  return code;
}