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
 int /*<<< orphan*/  async_request_quit (int /*<<< orphan*/ ) ; 
 scalar_t__ immediate_quit ; 
 int /*<<< orphan*/  mark_async_signal_handler_wrapper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigint_token ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 

void
handle_sigint (int sig)
{
  signal (sig, handle_sigint);

  /* If immediate_quit is set, we go ahead and process the SIGINT right
     away, even if we usually would defer this to the event loop. The
     assumption here is that it is safe to process ^C immediately if
     immediate_quit is set. If we didn't, SIGINT would be really
     processed only the next time through the event loop.  To get to
     that point, though, the command that we want to interrupt needs to
     finish first, which is unacceptable. */
  if (immediate_quit)
    async_request_quit (0);
  else
    /* If immediate quit is not set, we process SIGINT the next time
       through the loop, which is fine. */
    mark_async_signal_handler_wrapper (sigint_token);
}