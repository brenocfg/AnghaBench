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
typedef  int /*<<< orphan*/  ttrace_events ;
struct TYPE_2__ {int /*<<< orphan*/  tte_events; } ;
typedef  TYPE_1__ ttevent_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  TTEVT_VFORK ; 
 int /*<<< orphan*/  TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_GET_EVENT_MASK ; 
 int /*<<< orphan*/  TT_PROC_SET_EVENT_MASK ; 
 int call_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_on ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
hppa_disable_catch_vfork (int tid)
{
  int tt_status;
  ttevent_t ttrace_events;

  /* Get the set of events that are currently enabled. */
  tt_status = call_ttrace (TT_PROC_GET_EVENT_MASK,
			   tid,
			   (TTRACE_ARG_TYPE) & ttrace_events,
			   (TTRACE_ARG_TYPE) sizeof (ttrace_events),
			   TT_NIL);

  if (errno)
    perror_with_name ("ttrace");

  /* Remove vforks from that set. */
  ttrace_events.tte_events &= ~TTEVT_VFORK;

#ifdef THREAD_DEBUG
  if (debug_on)
    printf ("disable vfork, tid is %d\n", tid);
#endif
  tt_status = call_ttrace (TT_PROC_SET_EVENT_MASK,
			   tid,
			   (TTRACE_ARG_TYPE) & ttrace_events,
			   (TTRACE_ARG_TYPE) sizeof (ttrace_events),
			   TT_NIL);

  if (errno)
    perror_with_name ("ttrace");
}