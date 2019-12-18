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
struct lwp_info {int status; int /*<<< orphan*/  ptid; } ;

/* Variables and functions */
 double RAND_MAX ; 
 int /*<<< orphan*/  count_events_callback ; 
 scalar_t__ debug_lin_lwp ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 struct lwp_info* iterate_over_lwps (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  select_event_lwp_callback ; 
 int /*<<< orphan*/  select_singlestep_lwp_callback ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
select_event_lwp (struct lwp_info **orig_lp, int *status)
{
  int num_events = 0;
  int random_selector;
  struct lwp_info *event_lp;

  /* Record the wait status for the origional LWP.  */
  (*orig_lp)->status = *status;

  /* Give preference to any LWP that is being single-stepped.  */
  event_lp = iterate_over_lwps (select_singlestep_lwp_callback, NULL);
  if (event_lp != NULL)
    {
      if (debug_lin_lwp)
	fprintf_unfiltered (gdb_stdlog,
			    "SEL: Select single-step %s\n",
			    target_pid_to_str (event_lp->ptid));
    }
  else
    {
      /* No single-stepping LWP.  Select one at random, out of those
         which have had SIGTRAP events.  */

      /* First see how many SIGTRAP events we have.  */
      iterate_over_lwps (count_events_callback, &num_events);

      /* Now randomly pick a LWP out of those that have had a SIGTRAP.  */
      random_selector = (int)
	((num_events * (double) rand ()) / (RAND_MAX + 1.0));

      if (debug_lin_lwp && num_events > 1)
	fprintf_unfiltered (gdb_stdlog,
			    "SEL: Found %d SIGTRAP events, selecting #%d\n",
			    num_events, random_selector);

      event_lp = iterate_over_lwps (select_event_lwp_callback,
				    &random_selector);
    }

  if (event_lp != NULL)
    {
      /* Switch the event LWP.  */
      *orig_lp = event_lp;
      *status = event_lp->status;
    }

  /* Flush the wait status for the event LWP.  */
  (*orig_lp)->status = 0;
}