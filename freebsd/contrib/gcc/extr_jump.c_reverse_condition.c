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
#define  EQ 145 
#define  GE 144 
#define  GEU 143 
#define  GT 142 
#define  GTU 141 
#define  LE 140 
#define  LEU 139 
#define  LT 138 
#define  LTGT 137 
#define  LTU 136 
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

enum rtx_code
reverse_condition (enum rtx_code code)
{
  switch (code)
    {
    case EQ:
      return NE;
    case NE:
      return EQ;
    case GT:
      return LE;
    case GE:
      return LT;
    case LT:
      return GE;
    case LE:
      return GT;
    case GTU:
      return LEU;
    case GEU:
      return LTU;
    case LTU:
      return GEU;
    case LEU:
      return GTU;
    case UNORDERED:
      return ORDERED;
    case ORDERED:
      return UNORDERED;

    case UNLT:
    case UNLE:
    case UNGT:
    case UNGE:
    case UNEQ:
    case LTGT:
      return UNKNOWN;

    default:
      gcc_unreachable ();
    }
}