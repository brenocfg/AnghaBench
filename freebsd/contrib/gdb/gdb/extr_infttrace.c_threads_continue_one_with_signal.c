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
struct TYPE_3__ {scalar_t__ have_signal; int /*<<< orphan*/  handled; scalar_t__ terminated; } ;
typedef  TYPE_1__ thread_info ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  TT_LWP_CONTINUE ; 
 int /*<<< orphan*/  TT_NIL ; 
 int /*<<< orphan*/  TT_USE_CURRENT_PC ; 
 int /*<<< orphan*/  add_tthread (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_ttrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_on ; 
 TYPE_1__* find_thread_info (int /*<<< orphan*/ ) ; 
 int get_pid_for (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_from_gdb_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ target_signal_to_host (int) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
threads_continue_one_with_signal (lwpid_t gdb_tid, int signal)
{
  thread_info *p;
  lwpid_t real_tid;
  int real_pid;

#ifdef THREAD_DEBUG
  if (debug_on)
    printf ("Continuing one thread with a signal\n");
#endif

  real_tid = map_from_gdb_tid (gdb_tid);
  real_pid = get_pid_for (real_tid);

  p = find_thread_info (real_tid);
  if (NULL == p)
    {
      add_tthread (real_pid, real_tid);
    }

#ifdef THREAD_DEBUG
  if (debug_on)
    if (p->terminated)
      printf ("Why are we continuing a dead thread? (2)\n");
#endif

  if (!p->handled)
    warning ("Internal error: continuing unhandled thread.");

  p->have_signal = 0;

  call_ttrace (TT_LWP_CONTINUE,
	       gdb_tid,
	       TT_USE_CURRENT_PC,
	       (TTRACE_ARG_TYPE) target_signal_to_host (signal),
	       TT_NIL);
}