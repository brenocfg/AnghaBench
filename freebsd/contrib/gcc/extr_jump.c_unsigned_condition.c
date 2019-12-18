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
#define  EQ 137 
#define  GE 136 
#define  GEU 135 
#define  GT 134 
#define  GTU 133 
#define  LE 132 
#define  LEU 131 
#define  LT 130 
#define  LTU 129 
#define  NE 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

enum rtx_code
unsigned_condition (enum rtx_code code)
{
  switch (code)
    {
    case EQ:
    case NE:
    case GTU:
    case GEU:
    case LTU:
    case LEU:
      return code;

    case GT:
      return GTU;
    case GE:
      return GEU;
    case LT:
      return LTU;
    case LE:
      return LEU;

    default:
      gcc_unreachable ();
    }
}