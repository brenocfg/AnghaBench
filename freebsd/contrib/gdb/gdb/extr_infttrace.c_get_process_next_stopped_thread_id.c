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
struct TYPE_3__ {int /*<<< orphan*/  tts_lwpid; } ;
typedef  TYPE_1__ ttstate_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 scalar_t__ TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_GET_NEXT_LWP_STATE ; 
 int call_real_ttrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 

__attribute__((used)) static lwpid_t
get_process_next_stopped_thread_id (int pid, ttstate_t *thread_state)
{
  int tt_status;

  tt_status = call_real_ttrace (
				 TT_PROC_GET_NEXT_LWP_STATE,
				 (pid_t) pid,
				 (lwpid_t) TT_NIL,
				 (TTRACE_ARG_TYPE) thread_state,
				 (TTRACE_ARG_TYPE) sizeof (*thread_state),
				 TT_NIL);
  if (errno)
    perror_with_name ("ttrace");

  if (tt_status < 0)
    /* Failed
     */
    return 0;

  else if (tt_status == 0)
    {
      /* End of list, no next state.  Don't return the
       * tts_lwpid, as it's a meaningless "240".
       *
       * This is an HPUX "feature".
       */
      return 0;
    }

  return thread_state->tts_lwpid;
}