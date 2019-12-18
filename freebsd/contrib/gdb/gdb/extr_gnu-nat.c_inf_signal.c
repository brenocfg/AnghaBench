#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct exc_state {int /*<<< orphan*/  subcode; int /*<<< orphan*/  code; int /*<<< orphan*/  exception; int /*<<< orphan*/  reply; int /*<<< orphan*/  handler; } ;
struct TYPE_5__ {int sig; } ;
struct TYPE_6__ {scalar_t__ kind; TYPE_1__ value; } ;
struct inf_wait {TYPE_3__* thread; struct exc_state exc; TYPE_2__ status; } ;
struct inf {scalar_t__ stopped; int /*<<< orphan*/  event_port; TYPE_4__* task; struct inf_wait wait; } ;
typedef  scalar_t__ error_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_8__ {int /*<<< orphan*/  port; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; int /*<<< orphan*/  aborted; } ;

/* Variables and functions */
 scalar_t__ EIEIO ; 
 scalar_t__ INF_MSGPORT_RPC (struct inf*,int /*<<< orphan*/ ) ; 
 scalar_t__ INF_RESUME_MSGPORT_RPC (struct inf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND_ONCE ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MOVE_SEND_ONCE ; 
 int /*<<< orphan*/  NAME ; 
 scalar_t__ TARGET_WAITKIND_STOPPED ; 
 int _NSIG ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ exception_raise_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inf_debug (struct inf*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msg_sig_post_untraced (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_sig_post_untraced_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgport ; 
 int /*<<< orphan*/  refport ; 
 int /*<<< orphan*/  safe_strerror (scalar_t__) ; 
 int target_signal_to_host (int) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,...) ; 

void
inf_signal (struct inf *inf, enum target_signal sig)
{
  error_t err = 0;
  int host_sig = target_signal_to_host (sig);

#define NAME target_signal_to_name (sig)

  if (host_sig >= _NSIG)
    /* A mach exception.  Exceptions are encoded in the signal space by
       putting them after _NSIG; this assumes they're positive (and not
       extremely large)!  */
    {
      struct inf_wait *w = &inf->wait;
      if (w->status.kind == TARGET_WAITKIND_STOPPED
	  && w->status.value.sig == sig
	  && w->thread && !w->thread->aborted)
	/* We're passing through the last exception we received.  This is
	   kind of bogus, because exceptions are per-thread whereas gdb
	   treats signals as per-process.  We just forward the exception to
	   the correct handler, even it's not for the same thread as TID --
	   i.e., we pretend it's global.  */
	{
	  struct exc_state *e = &w->exc;
	  inf_debug (inf, "passing through exception:"
		     " task = %d, thread = %d, exc = %d"
		     ", code = %d, subcode = %d",
		     w->thread->port, inf->task->port,
		     e->exception, e->code, e->subcode);
	  err =
	    exception_raise_request (e->handler,
				     e->reply, MACH_MSG_TYPE_MOVE_SEND_ONCE,
				     w->thread->port, inf->task->port,
				     e->exception, e->code, e->subcode);
	}
      else
	error ("Can't forward spontaneous exception (%s).", NAME);
    }
  else
    /* A Unix signal.  */
  if (inf->stopped)
    /* The process is stopped and expecting a signal.  Just send off a
       request and let it get handled when we resume everything.  */
    {
      inf_debug (inf, "sending %s to stopped process", NAME);
      err =
	INF_MSGPORT_RPC (inf,
			 msg_sig_post_untraced_request (msgport,
							inf->event_port,
					       MACH_MSG_TYPE_MAKE_SEND_ONCE,
							host_sig, 0,
							refport));
      if (!err)
	/* Posting an untraced signal automatically continues it.
	   We clear this here rather than when we get the reply
	   because we'd rather assume it's not stopped when it
	   actually is, than the reverse.  */
	inf->stopped = 0;
    }
  else
    /* It's not expecting it.  We have to let just the signal thread
       run, and wait for it to get into a reasonable state before we
       can continue the rest of the process.  When we finally resume the
       process the signal we request will be the very first thing that
       happens. */
    {
      inf_debug (inf, "sending %s to unstopped process"
		 " (so resuming signal thread)", NAME);
      err =
	INF_RESUME_MSGPORT_RPC (inf,
				msg_sig_post_untraced (msgport, host_sig,
						       0, refport));
    }

  if (err == EIEIO)
    /* Can't do too much... */
    warning ("Can't deliver signal %s: No signal thread.", NAME);
  else if (err)
    warning ("Delivering signal %s: %s", NAME, safe_strerror (err));

#undef NAME
}