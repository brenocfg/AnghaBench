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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ABI_V4 ; 
 scalar_t__ CONST ; 
 scalar_t__ DEFAULT_ABI ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  TARGET_TOC ; 
 int /*<<< orphan*/  flag_pic ; 
 scalar_t__ small_data_operand (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
legitimate_small_data_p (enum machine_mode mode, rtx x)
{
  return (DEFAULT_ABI == ABI_V4
	  && !flag_pic && !TARGET_TOC
	  && (GET_CODE (x) == SYMBOL_REF || GET_CODE (x) == CONST)
	  && small_data_operand (x, mode));
}