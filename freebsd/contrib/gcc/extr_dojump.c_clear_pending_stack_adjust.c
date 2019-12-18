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
 scalar_t__ DECL_INLINE (int /*<<< orphan*/ ) ; 
 scalar_t__ EXIT_IGNORE_STACK ; 
 scalar_t__ current_function_calls_alloca ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  discard_pending_stack_adjust () ; 
 int /*<<< orphan*/  flag_no_inline ; 
 int /*<<< orphan*/  flag_omit_frame_pointer ; 
 scalar_t__ optimize ; 

void
clear_pending_stack_adjust (void)
{
  if (optimize > 0
      && (! flag_omit_frame_pointer || current_function_calls_alloca)
      && EXIT_IGNORE_STACK
      && ! (DECL_INLINE (current_function_decl) && ! flag_no_inline))
    discard_pending_stack_adjust ();
}