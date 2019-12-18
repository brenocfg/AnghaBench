#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tts_event; } ;
struct TYPE_6__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; TYPE_1__ last_stop_state; scalar_t__ have_state; int /*<<< orphan*/  handled; } ;
typedef  TYPE_2__ thread_info ;

/* Variables and functions */
 scalar_t__ TTEVT_FORK ; 
 scalar_t__ TTEVT_SIGNAL ; 
 scalar_t__ debug_on ; 
 int /*<<< orphan*/  get_printable_name_of_ttrace_event (scalar_t__) ; 
 int /*<<< orphan*/  print_tthread (TYPE_2__*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
thread_dropping_event_check (thread_info *p)
{
  if (!p->handled)
    {
      /*
       * This seems to happen when we "next" over a
       * "fork()" while following the parent.  If it's
       * the FORK event, that's ok.  If it's a SIGNAL
       * in the unfollowed child, that's ok to--but
       * how can we know that's what's going on?
       *
       * FIXME!
       */
      if (p->have_state)
	{
	  if (p->last_stop_state.tts_event == TTEVT_FORK)
	    {
	      /* Ok */
	      ;
	    }
	  else if (p->last_stop_state.tts_event == TTEVT_SIGNAL)
	    {
	      /* Ok, close eyes and let it happen.
	       */
	      ;
	    }
	  else
	    {
	      /* This shouldn't happen--we're dropping a
	       * real event.
	       */
	      warning ("About to continue process %d, thread %d with unhandled event %s.",
		       p->pid, p->tid,
		       get_printable_name_of_ttrace_event (
					     p->last_stop_state.tts_event));

#ifdef PARANOIA
	      if (debug_on)
		print_tthread (p);
#endif
	    }
	}
      else
	{
	  /* No saved state, have to assume it failed.
	   */
	  warning ("About to continue process %d, thread %d with unhandled event.",
		   p->pid, p->tid);
#ifdef PARANOIA
	  if (debug_on)
	    print_tthread (p);
#endif
	}
    }

}