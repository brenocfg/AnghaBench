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
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ ix86_fixup_binary_operands (int,int,scalar_t__*) ; 

void
ix86_fixup_binary_operands_no_copy (enum rtx_code code,
				    enum machine_mode mode, rtx operands[])
{
  rtx dst = ix86_fixup_binary_operands (code, mode, operands);
  gcc_assert (dst == operands[0]);
}