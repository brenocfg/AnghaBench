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

/* Variables and functions */
 int /*<<< orphan*/  clear_pending_stack_adjust () ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_jump (scalar_t__) ; 
 scalar_t__ gen_label_rtx () ; 
 scalar_t__ naked_return_label ; 

void
expand_naked_return (void)
{
  rtx end_label;

  clear_pending_stack_adjust ();
  do_pending_stack_adjust ();

  end_label = naked_return_label;
  if (end_label == 0)
    end_label = naked_return_label = gen_label_rtx ();

  emit_jump (end_label);
}