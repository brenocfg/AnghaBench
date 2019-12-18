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

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 int /*<<< orphan*/  adjust_stack (int /*<<< orphan*/ ) ; 
 scalar_t__ inhibit_defer_pop ; 
 scalar_t__ pending_stack_adjust ; 

void
do_pending_stack_adjust (void)
{
  if (inhibit_defer_pop == 0)
    {
      if (pending_stack_adjust != 0)
        adjust_stack (GEN_INT (pending_stack_adjust));
      pending_stack_adjust = 0;
    }
}