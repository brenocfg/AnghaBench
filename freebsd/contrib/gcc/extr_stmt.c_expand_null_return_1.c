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
 int /*<<< orphan*/  clear_pending_stack_adjust () ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_label ; 

__attribute__((used)) static void
expand_null_return_1 (void)
{
  clear_pending_stack_adjust ();
  do_pending_stack_adjust ();
  emit_jump (return_label);
}