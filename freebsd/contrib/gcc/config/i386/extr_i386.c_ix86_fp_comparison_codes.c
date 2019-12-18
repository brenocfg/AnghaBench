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
 int UNKNOWN ; 
#define  UNLE 130 
#define  UNLT 129 
#define  UNORDERED 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

void
ix86_fp_comparison_codes (enum rtx_code code, enum rtx_code *bypass_code,
			  enum rtx_code *first_code,
			  enum rtx_code *second_code)
{
  *first_code = code;
  *bypass_code = UNKNOWN;
  *second_code = UNKNOWN;

  /* The fcomi comparison sets flags as follows:

     cmp    ZF PF CF
     >      0  0  0
     <      0  0  1
     =      1  0  0
     un     1  1  1 */

  switch (code)
    {
    case GT:			/* GTU - CF=0 & ZF=0 */
    case GE:			/* GEU - CF=0 */
    case ORDERED:		/* PF=0 */
    case UNORDERED:		/* PF=1 */
    case UNEQ:			/* EQ - ZF=1 */
    case UNLT:			/* LTU - CF=1 */
    case UNLE:			/* LEU - CF=1 | ZF=1 */
    case LTGT:			/* EQ - ZF=0 */
      break;
    case LT:			/* LTU - CF=1 - fails on unordered */
      *first_code = UNLT;
      *bypass_code = UNORDERED;
      break;
    case LE:			/* LEU - CF=1 | ZF=1 - fails on unordered */
      *first_code = UNLE;
      *bypass_code = UNORDERED;
      break;
    case EQ:			/* EQ - ZF=1 - fails on unordered */
      *first_code = UNEQ;
      *bypass_code = UNORDERED;
      break;
    case NE:			/* NE - ZF=0 - fails on unordered */
      *first_code = LTGT;
      *second_code = UNORDERED;
      break;
    case UNGE:			/* GEU - CF=0 - fails on unordered */
      *first_code = GE;
      *second_code = UNORDERED;
      break;
    case UNGT:			/* GTU - CF=0 & ZF=0 - fails on unordered */
      *first_code = GT;
      *second_code = UNORDERED;
      break;
    default:
      gcc_unreachable ();
    }
  if (!TARGET_IEEE_FP)
    {
      *second_code = UNKNOWN;
      *bypass_code = UNKNOWN;
    }
}