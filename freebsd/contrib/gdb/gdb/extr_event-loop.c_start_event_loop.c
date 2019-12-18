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
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  after_char_processing_hook () ; 
 int catch_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_gdb_prompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_do_one_event ; 
 int /*<<< orphan*/  stub1 () ; 

void
start_event_loop (void)
{
  /* Loop until there is nothing to do. This is the entry point to the
     event loop engine. gdb_do_one_event, called via catch_errors()
     will process one event for each invocation.  It blocks waits for
     an event and then processes it.  >0 when an event is processed, 0
     when catch_errors() caught an error and <0 when there are no
     longer any event sources registered. */
  while (1)
    {
      int gdb_result;

      gdb_result = catch_errors (gdb_do_one_event, 0, "", RETURN_MASK_ALL);
      if (gdb_result < 0)
	break;

      /* If we long-jumped out of do_one_event, we probably
         didn't get around to resetting the prompt, which leaves
         readline in a messed-up state.  Reset it here. */

      if (gdb_result == 0)
	{
	  /* FIXME: this should really be a call to a hook that is
	     interface specific, because interfaces can display the
	     prompt in their own way. */
	  display_gdb_prompt (0);
	  /* This call looks bizarre, but it is required.  If the user
	     entered a command that caused an error,
	     after_char_processing_hook won't be called from
	     rl_callback_read_char_wrapper.  Using a cleanup there
	     won't work, since we want this function to be called
	     after a new prompt is printed.  */
	  if (after_char_processing_hook)
	    (*after_char_processing_hook) ();
	  /* Maybe better to set a flag to be checked somewhere as to
	     whether display the prompt or not. */
	}
    }

  /* We are done with the event loop. There are no more event sources
     to listen to.  So we exit GDB. */
  return;
}