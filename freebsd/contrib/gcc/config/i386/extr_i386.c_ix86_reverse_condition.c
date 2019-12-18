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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int CCFPUmode ; 
 int CCFPmode ; 
 int reverse_condition (int) ; 
 int reverse_condition_maybe_unordered (int) ; 

enum rtx_code
ix86_reverse_condition (enum rtx_code code, enum machine_mode mode)
{
  return (mode != CCFPmode && mode != CCFPUmode
	  ? reverse_condition (code)
	  : reverse_condition_maybe_unordered (code));
}