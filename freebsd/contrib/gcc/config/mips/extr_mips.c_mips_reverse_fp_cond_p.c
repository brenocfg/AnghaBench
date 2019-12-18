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
#define  LTGT 130 
#define  NE 129 
#define  ORDERED 128 
 int reverse_condition_maybe_unordered (int) ; 

__attribute__((used)) static bool
mips_reverse_fp_cond_p (enum rtx_code *code)
{
  switch (*code)
    {
    case NE:
    case LTGT:
    case ORDERED:
      *code = reverse_condition_maybe_unordered (*code);
      return true;

    default:
      return false;
    }
}