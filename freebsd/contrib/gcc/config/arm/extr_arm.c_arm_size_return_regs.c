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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int DECL_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 int GET_MODE (scalar_t__) ; 
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ current_function_return_rtx ; 

__attribute__((used)) static int
arm_size_return_regs (void)
{
  enum machine_mode mode;

  if (current_function_return_rtx != 0)
    mode = GET_MODE (current_function_return_rtx);
  else
    mode = DECL_MODE (DECL_RESULT (current_function_decl));

  return GET_MODE_SIZE (mode);
}