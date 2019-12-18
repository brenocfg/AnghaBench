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
 int /*<<< orphan*/  TARGET_CMOVE ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  ix86_fp_comparison_codes (int,int*,int*,int*) ; 

__attribute__((used)) static int
ix86_fp_comparison_fcomi_cost (enum rtx_code code)
{
  enum rtx_code bypass_code, first_code, second_code;
  /* Return arbitrarily high cost when instruction is not supported - this
     prevents gcc from using it.  */
  if (!TARGET_CMOVE)
    return 1024;
  ix86_fp_comparison_codes (code, &bypass_code, &first_code, &second_code);
  return (bypass_code != UNKNOWN || second_code != UNKNOWN) + 2;
}