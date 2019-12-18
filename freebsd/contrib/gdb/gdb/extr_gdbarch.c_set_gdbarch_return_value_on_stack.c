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
struct gdbarch {int /*<<< orphan*/  return_value_on_stack; } ;
typedef  int /*<<< orphan*/  gdbarch_return_value_on_stack_ftype ;

/* Variables and functions */

void
set_gdbarch_return_value_on_stack (struct gdbarch *gdbarch,
                                   gdbarch_return_value_on_stack_ftype return_value_on_stack)
{
  gdbarch->return_value_on_stack = return_value_on_stack;
}