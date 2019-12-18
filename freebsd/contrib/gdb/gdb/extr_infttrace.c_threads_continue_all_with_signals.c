#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tts_flags; scalar_t__ tts_event; } ;
typedef  TYPE_1__ ttstate_t ;
struct TYPE_9__ {int handled; int seen; scalar_t__ tid; int signal_value; scalar_t__ stepping_mode; scalar_t__ have_signal; struct TYPE_9__* next; scalar_t__ terminated; } ;
typedef  TYPE_2__ thread_info ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_10__ {TYPE_2__* head; } ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 scalar_t__ DO_STEP ; 
 scalar_t__ TTEVT_NONE ; 
 int TTS_STATEMASK ; 
 int TTS_WASSUSPENDED ; 
 int /*<<< orphan*/  TT_LWP_CONTINUE ; 
 int /*<<< orphan*/  TT_LWP_SINGLE ; 
 int /*<<< orphan*/  TT_NIL ; 
 int /*<<< orphan*/  TT_USE_CURRENT_PC ; 
 int /*<<< orphan*/  add_tthread (int,scalar_t__) ; 
 int /*<<< orphan*/  call_ttrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_on ; 
 TYPE_2__* find_thread_info (scalar_t__) ; 
 int get_pid_for (scalar_t__) ; 
 scalar_t__ get_printable_name_of_ttrace_event (scalar_t__) ; 
 scalar_t__ get_process_first_stopped_thread_id (int,TYPE_1__*) ; 
 scalar_t__ get_process_next_stopped_thread_id (int,TYPE_1__*) ; 
 scalar_t__ map_from_gdb_tid (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  set_all_unseen () ; 
 scalar_t__ target_signal_to_host (int) ; 
 int /*<<< orphan*/  thread_dropping_event_check (TYPE_2__*) ; 
 TYPE_3__ thread_head ; 
 int /*<<< orphan*/  update_thread_list () ; 
 int /*<<< orphan*/  warning (char*,scalar_t__) ; 

__attribute__((used)) static void
threads_continue_all_with_signals (lwpid_t gdb_tid, int signal)
{
  thread_info *p;
  int thread_signal;
  lwpid_t real_tid;
  lwpid_t scan_tid;
  ttstate_t state;
  int real_pid;

#ifdef THREAD_DEBUG
  if (debug_on)
    printf ("Using loop over threads to resume with signals\n");
#endif

  /* Scan and update thread list.
   */
  set_all_unseen ();
  real_tid = map_from_gdb_tid (gdb_tid);
  real_pid = get_pid_for (real_tid);

  scan_tid = get_process_first_stopped_thread_id (real_pid, &state);
  while (0 != scan_tid)
    {

#ifdef THREAD_DEBUG
      if (debug_on)
	if ((state.tts_flags & TTS_STATEMASK) != TTS_WASSUSPENDED)
	  warning ("About to continue non-stopped thread %d\n", scan_tid);
#endif

      p = find_thread_info (scan_tid);
      if (NULL == p)
	{
	  add_tthread (real_pid, scan_tid);
	  p = find_thread_info (scan_tid);

	  /* This is either a newly-created thread or the
	   * result of a fork; in either case there's no
	   * actual event to worry about.
	   */
	  p->handled = 1;

	  if (state.tts_event != TTEVT_NONE)
	    {
	      /* Oops, do need to worry!
	       */
	      warning ("Unexpected thread with \"%s\" event.",
		       get_printable_name_of_ttrace_event (state.tts_event));
	    }
	}

#ifdef THREAD_DEBUG
      if (debug_on)
	if (p->terminated)
	  printf ("Why are we continuing a dead thread? (1)\n");
#endif

      p->seen = 1;

      scan_tid = get_process_next_stopped_thread_id (real_pid, &state);
    }

  /* Remove unseen threads from our list.
   */
  update_thread_list ();

  /* Continue the threads.
   */
  for (p = thread_head.head; p; p = p->next)
    {

      /* Sanity check.
       */
      thread_dropping_event_check (p);

      /* Pass the correct signals along.
       */
      if (p->tid == real_tid)
	{
	  thread_signal = signal;
	  p->have_signal = 0;
	}
      else if (p->have_signal)
	{
	  thread_signal = p->signal_value;
	  p->have_signal = 0;
	}
      else
	thread_signal = 0;

      if (p->stepping_mode == DO_STEP)
	{
	  call_ttrace (
			TT_LWP_SINGLE,
			p->tid,
			TT_USE_CURRENT_PC,
			(TTRACE_ARG_TYPE) target_signal_to_host (signal),
			TT_NIL);
	}
      else
	{
	  /* Continue this thread (default case).
	   */
	  call_ttrace (
			TT_LWP_CONTINUE,
			p->tid,
			TT_USE_CURRENT_PC,
		    (TTRACE_ARG_TYPE) target_signal_to_host (thread_signal),
			TT_NIL);
	}
    }
}