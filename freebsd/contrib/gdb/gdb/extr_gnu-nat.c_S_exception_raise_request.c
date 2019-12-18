#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_t ;
typedef  scalar_t__ task_t ;
struct proc {scalar_t__ exc_port; scalar_t__ saved_exc_port; int /*<<< orphan*/  aborted; } ;
struct TYPE_8__ {int /*<<< orphan*/  sig; } ;
struct TYPE_9__ {TYPE_3__ value; int /*<<< orphan*/  kind; } ;
struct TYPE_7__ {scalar_t__ handler; int exception; int code; int subcode; scalar_t__ reply; } ;
struct TYPE_10__ {int suppress; TYPE_4__ status; TYPE_2__ exc; struct proc* thread; } ;
struct inf {TYPE_5__ wait; TYPE_1__* task; } ;
typedef  scalar_t__ mach_port_t ;
typedef  int /*<<< orphan*/  error_t ;
struct TYPE_6__ {scalar_t__ saved_exc_port; scalar_t__ exc_port; } ;

/* Variables and functions */
 int EXC_BREAKPOINT ; 
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_SEND ; 
 int /*<<< orphan*/  TARGET_SIGNAL_TRAP ; 
 int /*<<< orphan*/  TARGET_WAITKIND_STOPPED ; 
 scalar_t__ _NSIG ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inf_debug (struct inf*,char*,scalar_t__,...) ; 
 struct proc* inf_port_to_thread (struct inf*,scalar_t__) ; 
 int /*<<< orphan*/  inf_update_procs (struct inf*) ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mach_port_mod_refs (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  target_signal_from_host (scalar_t__) ; 
 struct inf* waiting_inf ; 

error_t
S_exception_raise_request (mach_port_t port, mach_port_t reply_port,
			   thread_t thread_port, task_t task_port,
			   int exception, int code, int subcode)
{
  struct inf *inf = waiting_inf;
  struct proc *thread = inf_port_to_thread (inf, thread_port);

  inf_debug (waiting_inf,
	     "thread = %d, task = %d, exc = %d, code = %d, subcode = %d",
	     thread_port, task_port, exception, code, subcode);

  if (!thread)
    /* We don't know about thread?  */
    {
      inf_update_procs (inf);
      thread = inf_port_to_thread (inf, thread_port);
      if (!thread)
	/* Give up, the generating thread is gone.  */
	return 0;
    }

  mach_port_deallocate (mach_task_self (), thread_port);
  mach_port_deallocate (mach_task_self (), task_port);

  if (!thread->aborted)
    /* THREAD hasn't been aborted since this exception happened (abortion
       clears any exception state), so it must be real.  */
    {
      /* Store away the details; this will destroy any previous info.  */
      inf->wait.thread = thread;

      inf->wait.status.kind = TARGET_WAITKIND_STOPPED;

      if (exception == EXC_BREAKPOINT)
	/* GDB likes to get SIGTRAP for breakpoints.  */
	{
	  inf->wait.status.value.sig = TARGET_SIGNAL_TRAP;
	  mach_port_deallocate (mach_task_self (), reply_port);
	}
      else
	/* Record the exception so that we can forward it later.  */
	{
	  if (thread->exc_port == port)
	    {
	      inf_debug (waiting_inf, "Handler is thread exception port <%d>",
			 thread->saved_exc_port);
	      inf->wait.exc.handler = thread->saved_exc_port;
	    }
	  else
	    {
	      inf_debug (waiting_inf, "Handler is task exception port <%d>",
			 inf->task->saved_exc_port);
	      inf->wait.exc.handler = inf->task->saved_exc_port;
	      gdb_assert (inf->task->exc_port == port);
	    }
	  if (inf->wait.exc.handler != MACH_PORT_NULL)
	    /* Add a reference to the exception handler. */
	    mach_port_mod_refs (mach_task_self (),
				inf->wait.exc.handler, MACH_PORT_RIGHT_SEND,
				1);

	  inf->wait.exc.exception = exception;
	  inf->wait.exc.code = code;
	  inf->wait.exc.subcode = subcode;
	  inf->wait.exc.reply = reply_port;

	  /* Exceptions are encoded in the signal space by putting them after
	     _NSIG; this assumes they're positive (and not extremely large)! */
	  inf->wait.status.value.sig =
	    target_signal_from_host (_NSIG + exception);
	}
    }
  else
    /* A supppressed exception, which ignore.  */
    {
      inf->wait.suppress = 1;
      mach_port_deallocate (mach_task_self (), reply_port);
    }

  return 0;
}