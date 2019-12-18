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
 int /*<<< orphan*/  SETUP_FRAME_ADDRESSES () ; 
 int current_function_has_nonlocal_label ; 

void
expand_builtin_unwind_init (void)
{
  /* Set this so all the registers get saved in our frame; we need to be
     able to copy the saved values for any registers from frames we unwind.  */
  current_function_has_nonlocal_label = 1;

#ifdef SETUP_FRAME_ADDRESSES
  SETUP_FRAME_ADDRESSES ();
#endif
}