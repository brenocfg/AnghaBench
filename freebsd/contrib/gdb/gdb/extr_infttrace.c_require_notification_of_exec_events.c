#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ttstate_t ;
struct TYPE_2__ {int /*<<< orphan*/  tte_events; int /*<<< orphan*/  tte_opts; int /*<<< orphan*/  tte_signals; } ;
typedef  TYPE_1__ ttevent_t ;
typedef  int /*<<< orphan*/  notifiable_events ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  TTEO_NOSTRCCHLD ; 
 int /*<<< orphan*/  TTEO_PROC_INHERIT ; 
 int /*<<< orphan*/  TTEVT_DEFAULT ; 
 int /*<<< orphan*/  TTEVT_EXEC ; 
 int /*<<< orphan*/  TTEVT_EXIT ; 
 scalar_t__ TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_SET_EVENT_MASK ; 
 int call_real_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ debug_on ; 
 scalar_t__ not_same_real_pid ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
require_notification_of_exec_events (int real_pid)
{
  int tt_status;
  ttevent_t notifiable_events;

  lwpid_t tid;
  ttstate_t thread_state;

#ifdef THREAD_DEBUG
  if (debug_on)
    printf ("Require notif, pid is %d\n", real_pid);
#endif

  /* Temporary HACK: tell inftarg.c/child_wait to not
   * loop until pids are the same.
   */
  not_same_real_pid = 0;

  sigemptyset (&notifiable_events.tte_signals);
  notifiable_events.tte_opts = TTEO_NOSTRCCHLD;

  /* This ensures that forked children don't inherit their parent's
   * event mask, which we're setting here.
   */
  notifiable_events.tte_opts &= ~TTEO_PROC_INHERIT;

  notifiable_events.tte_events = TTEVT_DEFAULT;
  notifiable_events.tte_events |= TTEVT_EXEC;
  notifiable_events.tte_events |= TTEVT_EXIT;

  tt_status = call_real_ttrace (
				 TT_PROC_SET_EVENT_MASK,
				 real_pid,
				 (lwpid_t) TT_NIL,
				 (TTRACE_ARG_TYPE) & notifiable_events,
			       (TTRACE_ARG_TYPE) sizeof (notifiable_events),
				 TT_NIL);
}