#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 scalar_t__ TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_STOP ; 
 int call_real_ttrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 

__attribute__((used)) static void
stop_all_threads_of_process (pid_t real_pid)
{
  int ttw_status;

  ttw_status = call_real_ttrace (TT_PROC_STOP,
				 (pid_t) real_pid,
				 (lwpid_t) TT_NIL,
				 (TTRACE_ARG_TYPE) TT_NIL,
				 (TTRACE_ARG_TYPE) TT_NIL,
				 TT_NIL);
  if (errno)
    perror_with_name ("ttrace stop of other threads");
}