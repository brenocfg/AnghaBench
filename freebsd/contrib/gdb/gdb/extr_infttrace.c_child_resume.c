#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int have_signal; int signal_value; scalar_t__ stepping_mode; scalar_t__ terminated; } ;
typedef  TYPE_1__ thread_info ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  scalar_t__ process_state_t ;
typedef  scalar_t__ lwpid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 scalar_t__ DO_CONTINUE ; 
 scalar_t__ DO_DEFAULT ; 
 scalar_t__ DO_STEP ; 
 scalar_t__ FAKE_STEPPING ; 
 scalar_t__ INFTTRACE_ALL_THREADS ; 
 scalar_t__ PIDGET (int /*<<< orphan*/ ) ; 
 scalar_t__ RUNNING ; 
 int /*<<< orphan*/  TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_CONTINUE ; 
 int /*<<< orphan*/  call_ttrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_all_handled () ; 
 int /*<<< orphan*/  clear_all_stepping_mode () ; 
 int /*<<< orphan*/  clear_handled (scalar_t__) ; 
 int /*<<< orphan*/  clear_stepping_mode (scalar_t__) ; 
 scalar_t__ debug_on ; 
 TYPE_1__* find_thread_info (scalar_t__) ; 
 char* get_printable_name_of_process_state (scalar_t__) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ map_from_gdb_tid (scalar_t__) ; 
 scalar_t__ more_events_left ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ process_state ; 
 int /*<<< orphan*/  thread_fake_step (scalar_t__,int) ; 
 int /*<<< orphan*/  threads_continue_all_but_one (scalar_t__,int) ; 
 int /*<<< orphan*/  threads_continue_all_with_signals (scalar_t__,int) ; 
 int /*<<< orphan*/  threads_continue_one_with_signal (scalar_t__,int) ; 
 scalar_t__ vfork_in_flight ; 
 scalar_t__ vforking_child_pid ; 
 int /*<<< orphan*/  warning (char*,...) ; 

void
child_resume (ptid_t ptid, int step, enum target_signal signal)
{
  int resume_all_threads;
  lwpid_t tid;
  process_state_t new_process_state;
  lwpid_t gdb_tid = PIDGET (ptid);

  resume_all_threads =
    (gdb_tid == INFTTRACE_ALL_THREADS) ||
    (vfork_in_flight);

  if (resume_all_threads)
    {
      /* Resume all threads, but first pick a tid value
       * so we can get the pid when in call_ttrace doing
       * the map.
       */
      if (vfork_in_flight)
	tid = vforking_child_pid;
      else
	tid = map_from_gdb_tid (PIDGET (inferior_ptid));
    }
  else
    tid = map_from_gdb_tid (gdb_tid);

#ifdef THREAD_DEBUG
  if (debug_on)
    {
      if (more_events_left)
	printf ("More events; ");

      if (signal != 0)
	printf ("Sending signal %d; ", signal);

      if (resume_all_threads)
	{
	  if (step == 0)
	    printf ("Continue process %d\n", tid);
	  else
	    printf ("Step/continue thread %d\n", tid);
	}
      else
	{
	  if (step == 0)
	    printf ("Continue thread %d\n", tid);
	  else
	    printf ("Step just thread %d\n", tid);
	}

      if (vfork_in_flight)
	printf ("Vfork in flight\n");
    }
#endif

  if (process_state == RUNNING)
    warning ("Internal error in resume logic; doing resume or step anyway.");

  if (!step			/* Asked to continue...       */
      && resume_all_threads	/* whole process..            */
      && signal != 0		/* with a signal...           */
      && more_events_left > 0)
    {				/* but we can't yet--save it! */

      /* Continue with signal means we have to set the pending
       * signal value for this thread.
       */
      thread_info *k;

#ifdef THREAD_DEBUG
      if (debug_on)
	printf ("Saving signal %d for thread %d\n", signal, tid);
#endif

      k = find_thread_info (tid);
      if (k != NULL)
	{
	  k->have_signal = 1;
	  k->signal_value = signal;

#ifdef THREAD_DEBUG
	  if (debug_on)
	    if (k->terminated)
	      printf ("Why are we continuing a dead thread? (3)\n");
#endif

	}

#ifdef THREAD_DEBUG
      else if (debug_on)
	{
	  printf ("No thread info for tid %d\n", tid);
	}
#endif
    }

  /* Are we faking this "continue" or "step"?

   * We used to do steps by continuing all the threads for 
   * which the events had been handled already.  While
   * conceptually nicer (hides it all in a lower level), this
   * can lead to starvation and a hang (e.g. all but one thread
   * are unhandled at a breakpoint just before a "join" operation,
   * and one thread is in the join, and the user wants to step that
   * thread).
   */
  if (resume_all_threads	/* Whole process, therefore user command */
      && more_events_left > 0)
    {				/* But we can't do this yet--fake it! */
      thread_info *p;

      if (!step)
	{
	  /* No need to do any notes on a per-thread
	   * basis--we're done!
	   */
#ifdef WAIT_BUFFER_DEBUG
	  if (debug_on)
	    printf ("Faking a process resume.\n");
#endif

	  return;
	}
      else
	{

#ifdef WAIT_BUFFER_DEBUG
	  if (debug_on)
	    printf ("Faking a process step.\n");
#endif

	}

      p = find_thread_info (tid);
      if (p == NULL)
	{
	  warning ("No thread information for tid %d, 'next' command ignored.\n", tid);
	  return;
	}
      else
	{

#ifdef THREAD_DEBUG
	  if (debug_on)
	    if (p->terminated)
	      printf ("Why are we continuing a dead thread? (3.5)\n");
#endif

	  if (p->stepping_mode != DO_DEFAULT)
	    {
	      warning ("Step or continue command applied to thread which is already stepping or continuing; command ignored.");

	      return;
	    }

	  if (step)
	    p->stepping_mode = DO_STEP;
	  else
	    p->stepping_mode = DO_CONTINUE;

	  return;
	}			/* Have thread info */
    }				/* Must fake step or go */

  /* Execept for fake-steps, from here on we know we are
   * going to wind up with a running process which will
   * need a real wait.
   */
  new_process_state = RUNNING;

  /* An address of TT_USE_CURRENT_PC tells ttrace to continue from where
   * it was.  (If GDB wanted it to start some other way, we have already
   * written a new PC value to the child.)
   *
   * If this system does not support PT_STEP, a higher level function will
   * have called single_step() to transmute the step request into a
   * continue request (by setting breakpoints on all possible successor
   * instructions), so we don't have to worry about that here.
   */
  if (step)
    {
      if (resume_all_threads)
	{
	  /*
	   * Regular user step: other threads get a "continue".
	   */
	  threads_continue_all_but_one (tid, signal);
	  clear_all_handled ();
	  clear_all_stepping_mode ();
	}

      else
	{
	  /* "Fake step": gdb is stepping one thread over a
	   * breakpoint, watchpoint, or out of a library load
	   * event, etc.  The rest just stay where they are.
	   *
	   * Also used when there are pending events: we really
	   * step the current thread, but leave the rest stopped.
	   * Users can't request this, but "wait_for_inferior"
	   * does--a lot!
	   */
	  thread_fake_step (tid, signal);

	  /* Clear the "handled" state of this thread, because
	   * we'll soon get a new event for it.  Other events
	   * stay as they were.
	   */
	  clear_handled (tid);
	  clear_stepping_mode (tid);
	  new_process_state = FAKE_STEPPING;
	}
    }

  else
    {
      /* TT_LWP_CONTINUE can pass signals to threads, TT_PROC_CONTINUE can't.
	 Therefore, we really can't use TT_PROC_CONTINUE here.

	 Consider a process which stopped due to signal which gdb decides
	 to handle and not pass on to the inferior.  In that case we must
	 clear the pending signal by restarting the inferior using
	 TT_LWP_CONTINUE and pass zero as the signal number.  Else the
	 pending signal will be passed to the inferior.  interrupt.exp
	 in the testsuite does this precise thing and fails due to the
	 unwanted signal delivery to the inferior.  */
      /* drow/2002-12-05: However, note that we must use TT_PROC_CONTINUE
	 if we are tracing a vfork.  */
      if (vfork_in_flight)
	{
	  call_ttrace (TT_PROC_CONTINUE, tid, TT_NIL, TT_NIL, TT_NIL);
	  clear_all_handled ();
	  clear_all_stepping_mode ();
	}
      else if (resume_all_threads)
	{
#ifdef THREAD_DEBUG
	  if (debug_on)
	    printf ("Doing a continue by loop of all threads\n");
#endif

	  threads_continue_all_with_signals (tid, signal);

	  clear_all_handled ();
	  clear_all_stepping_mode ();
	}
      else
	{
#ifdef THREAD_DEBUG
	  printf ("Doing a continue w/signal of just thread %d\n", tid);
#endif

	  threads_continue_one_with_signal (tid, signal);

	  /* Clear the "handled" state of this thread, because we
	     will soon get a new event for it.  Other events can
	     stay as they were.  */
	  clear_handled (tid);
	  clear_stepping_mode (tid);
	}
    }

  process_state = new_process_state;

#ifdef WAIT_BUFFER_DEBUG
  if (debug_on)
    printf ("Process set to %s\n",
	    get_printable_name_of_process_state (process_state));
#endif

}