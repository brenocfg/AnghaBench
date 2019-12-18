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
struct TYPE_5__ {int tts_event; int tts_scno; } ;
typedef  TYPE_1__ ttstate_t ;
typedef  int /*<<< orphan*/  ttrace_state ;
struct TYPE_6__ {int /*<<< orphan*/  last_stop_state; } ;
typedef  TYPE_2__ thread_info ;
typedef  enum target_waitkind { ____Placeholder_target_waitkind } target_waitkind ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 int TARGET_WAITKIND_SPURIOUS ; 
 int TARGET_WAITKIND_SYSCALL_ENTRY ; 
 int TARGET_WAITKIND_SYSCALL_RETURN ; 
 int TTEVT_SYSCALL_ENTRY ; 
 int TTEVT_SYSCALL_RETURN ; 
 int /*<<< orphan*/  TT_LWP_GET_STATE ; 
 int /*<<< orphan*/  TT_NIL ; 
 int call_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_ttstate_t (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 TYPE_2__* find_thread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_from_gdb_tid (int) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 

int
hpux_has_syscall_event (int pid, enum target_waitkind *kind, int *syscall_id)
{
  int tt_status;
  ttstate_t ttrace_state;
  thread_info *tinfo;

  /* Do we have cached thread state that we can consult?  If so, use it. */
  tinfo = find_thread_info (map_from_gdb_tid (pid));
  if (tinfo != NULL)
    copy_ttstate_t (&ttrace_state, &tinfo->last_stop_state);

  /* Nope, must read the thread's current state */
  else
    {
      tt_status = call_ttrace (TT_LWP_GET_STATE,
			       pid,
			       (TTRACE_ARG_TYPE) & ttrace_state,
			       (TTRACE_ARG_TYPE) sizeof (ttrace_state),
			       TT_NIL);

      if (errno)
	perror_with_name ("ttrace");

      if (tt_status < 0)
	return 0;
    }

  *kind = TARGET_WAITKIND_SPURIOUS;	/* Until proven otherwise... */
  *syscall_id = -1;

  if (ttrace_state.tts_event & TTEVT_SYSCALL_ENTRY)
    *kind = TARGET_WAITKIND_SYSCALL_ENTRY;
  else if (ttrace_state.tts_event & TTEVT_SYSCALL_RETURN)
    *kind = TARGET_WAITKIND_SYSCALL_RETURN;
  else
    return 0;

  *syscall_id = ttrace_state.tts_scno;
  return 1;
}