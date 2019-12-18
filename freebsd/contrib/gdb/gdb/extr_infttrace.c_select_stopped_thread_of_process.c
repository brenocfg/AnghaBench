#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int tts_signo; } ;
struct TYPE_10__ {TYPE_1__ tts_signal; } ;
struct TYPE_11__ {scalar_t__ tts_event; scalar_t__ tts_lwpid; TYPE_2__ tts_u; } ;
typedef  TYPE_3__ ttstate_t ;
typedef  scalar_t__ lwpid_t ;

/* Variables and functions */
 scalar_t__ TTEVT_NONE ; 
 scalar_t__ TTEVT_SIGNAL ; 
 int /*<<< orphan*/  breakpoint_here_p (scalar_t__) ; 
 int /*<<< orphan*/  can_touch_threads_of_process (int,scalar_t__) ; 
 int /*<<< orphan*/  copy_ttstate_t (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ debug_on ; 
 scalar_t__ doing_fake_step ; 
 scalar_t__ fake_step_tid ; 
 char* get_printable_name_of_ttrace_event (scalar_t__) ; 
 scalar_t__ get_process_first_stopped_thread_id (int,TYPE_3__*) ; 
 scalar_t__ get_process_next_stopped_thread_id (int,TYPE_3__*) ; 
 scalar_t__ get_raw_pc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  set_handled (int,scalar_t__) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  was_handled (scalar_t__) ; 

__attribute__((used)) static int
select_stopped_thread_of_process (int pid, ttstate_t *tsp)
{
  lwpid_t candidate_tid, tid;
  ttstate_t candidate_tstate, tstate;

  /* If we're not allowed to touch the process now, then just
   * return the current value of *TSP.
   *
   * This supports "vfork".  It's ok, really, to double the
   * current event (the child EXEC, we hope!).
   */
  if (!can_touch_threads_of_process (pid, tsp->tts_event))
    return 1;

  /* Decide which of (possibly more than one) events to
   * return as the first one.  We scan them all so that
   * we always return the result of a fake-step first.
   */
  candidate_tid = 0;
  for (tid = get_process_first_stopped_thread_id (pid, &tstate);
       tid != 0;
       tid = get_process_next_stopped_thread_id (pid, &tstate))
    {
      /* TTEVT_NONE events are uninteresting to our clients.  They're
       * an artifact of our "stop the world" model--the thread is
       * stopped because we stopped it.
       */
      if (tstate.tts_event == TTEVT_NONE)
	{
	  set_handled (pid, tstate.tts_lwpid);
	}

      /* Did we just single-step a single thread, without letting any
       * of the others run?  Is this an event for that thread?
       *
       * If so, we believe our client would prefer to see this event
       * over any others.  (Typically the client wants to just push
       * one thread a little farther forward, and then go around
       * checking for what all threads are doing.)
       */
      else if (doing_fake_step && (tstate.tts_lwpid == fake_step_tid))
	{
#ifdef WAIT_BUFFER_DEBUG
	  /* It's possible here to see either a SIGTRAP (due to
	   * successful completion of a step) or a SYSCALL_ENTRY
	   * (due to a step completion with active hardware
	   * watchpoints).
	   */
	  if (debug_on)
	    printf ("Ending fake step with tid %d, state %s\n",
		    tstate.tts_lwpid,
		    get_printable_name_of_ttrace_event (tstate.tts_event));
#endif

	  /* Remember this one, and throw away any previous
	   * candidate.
	   */
	  candidate_tid = tstate.tts_lwpid;
	  candidate_tstate = tstate;
	}

#ifdef FORGET_DELETED_BPTS

      /* We can't just do this, as if we do, and then wind
       * up the loop with no unhandled events, we need to
       * handle that case--the appropriate reaction is to
       * just continue, but there's no easy way to do that.
       *
       * Better to put this in the ttrace_wait call--if, when
       * we fake a wait, we update our events based on the
       * breakpoint_here_pc call and find there are no more events,
       * then we better continue and so on.
       *
       * Or we could put it in the next/continue fake.
       * But it has to go in the buffering code, not in the
       * real go/wait code.
       */
      else if ((TTEVT_SIGNAL == tstate.tts_event)
	       && (5 == tstate.tts_u.tts_signal.tts_signo)
	       && (0 != get_raw_pc (tstate.tts_lwpid))
	       && !breakpoint_here_p (get_raw_pc (tstate.tts_lwpid)))
	{
	  /*
	   * If the user deleted a breakpoint while this
	   * breakpoint-hit event was buffered, we can forget
	   * it now.
	   */
#ifdef WAIT_BUFFER_DEBUG
	  if (debug_on)
	    printf ("Forgetting deleted bp hit for thread %d\n",
		    tstate.tts_lwpid);
#endif

	  set_handled (pid, tstate.tts_lwpid);
	}
#endif

      /* Else, is this the first "unhandled" event?  If so,
       * we believe our client wants to see it (if we don't
       * see a fake-step later on in the scan).
       */
      else if (!was_handled (tstate.tts_lwpid) && candidate_tid == 0)
	{
	  candidate_tid = tstate.tts_lwpid;
	  candidate_tstate = tstate;
	}

      /* This is either an event that has already been "handled",
       * and thus we believe is uninteresting to our client, or we
       * already have a candidate event.  Ignore it...
       */
    }

  /* What do we report?
   */
  if (doing_fake_step)
    {
      if (candidate_tid == fake_step_tid)
	{
	  /* Fake step.
	   */
	  tstate = candidate_tstate;
	}
      else
	{
	  warning ("Internal error: fake-step failed to complete.");
	  return 0;
	}
    }
  else if (candidate_tid != 0)
    {
      /* Found a candidate unhandled event.
       */
      tstate = candidate_tstate;
    }
  else if (tid != 0)
    {
      warning ("Internal error in call of ttrace_wait.");
      return 0;
    }
  else
    {
      warning ("Internal error: no unhandled thread event to select");
      return 0;
    }

  copy_ttstate_t (tsp, &tstate);
  return 1;
}