#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tts_signo; } ;
struct TYPE_7__ {TYPE_1__ tts_signal; } ;
struct TYPE_8__ {scalar_t__ tts_event; TYPE_2__ tts_u; } ;
typedef  TYPE_3__ ttstate_t ;
typedef  int lwpid_t ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ TTEVT_NONE ; 
 scalar_t__ TTEVT_SIGNAL ; 
 scalar_t__ debug_on ; 
 char* get_printable_name_of_ttrace_event (scalar_t__) ; 
 int get_process_first_stopped_thread_id (int,TYPE_3__*) ; 
 int get_process_next_stopped_thread_id (int,TYPE_3__*) ; 
 int get_raw_pc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ was_handled (int) ; 

__attribute__((used)) static int
count_unhandled_events (int real_pid, lwpid_t real_tid)
{
  ttstate_t tstate;
  lwpid_t ttid;
  int events_left;

  /* Ok, find out how many threads have real events to report.
   */
  events_left = 0;
  ttid = get_process_first_stopped_thread_id (real_pid, &tstate);

#ifdef THREAD_DEBUG
  if (debug_on)
    {
      if (ttid == 0)
	printf ("Process %d has no threads\n", real_pid);
      else
	printf ("Process %d has these threads:\n", real_pid);
    }
#endif

  while (ttid > 0)
    {
      if (tstate.tts_event != TTEVT_NONE
	  && !was_handled (ttid))
	{
	  /* TTEVT_NONE implies we just stopped it ourselves
	   * because we're the stop-the-world guys, so it's
	   * not an event from our point of view.
	   *
	   * If "was_handled" is true, this is an event we
	   * already handled, so don't count it.
	   *
	   * Note that we don't count the thread with the
	   * currently-reported event, as it's already marked
	   * as handled.
	   */
	  events_left++;
	}

#if defined( THREAD_DEBUG ) || defined( WAIT_BUFFER_DEBUG )
      if (debug_on)
	{
	  if (ttid == real_tid)
	    printf ("*");	/* Thread we're reporting */
	  else
	    printf (" ");

	  if (tstate.tts_event != TTEVT_NONE)
	    printf ("+");	/* Thread with a real event */
	  else
	    printf (" ");

	  if (was_handled (ttid))
	    printf ("h");	/* Thread has been handled */
	  else
	    printf (" ");

	  printf (" %d, with event %s", ttid,
		  get_printable_name_of_ttrace_event (tstate.tts_event));

	  if (tstate.tts_event == TTEVT_SIGNAL
	      && 5 == tstate.tts_u.tts_signal.tts_signo)
	    {
	      CORE_ADDR pc_val;

	      pc_val = get_raw_pc (ttid);

	      if (pc_val > 0)
		printf (" breakpoint at 0x%x\n", pc_val);
	      else
		printf (" bpt, can't fetch pc.\n");
	    }
	  else
	    printf ("\n");
	}
#endif

      ttid = get_process_next_stopped_thread_id (real_pid, &tstate);
    }

#if defined( THREAD_DEBUG ) || defined( WAIT_BUFFER_DEBUG )
  if (debug_on)
    if (events_left > 0)
      printf ("There are thus %d pending events\n", events_left);
#endif

  return events_left;
}