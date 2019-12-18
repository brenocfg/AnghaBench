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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_PEEKUSER ; 
 scalar_t__ debug_lin_lwp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  is_lwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lin_lwp_thread_alive (ptid_t ptid)
{
  gdb_assert (is_lwp (ptid));

  errno = 0;
  ptrace (PTRACE_PEEKUSER, GET_LWP (ptid), 0, 0);
  if (debug_lin_lwp)
    fprintf_unfiltered (gdb_stdlog,
			"LLTA: PTRACE_PEEKUSER %s, 0, 0 (%s)\n",
			target_pid_to_str (ptid),
			errno ? safe_strerror (errno) : "OK");
  if (errno)
    return 0;

  return 1;
}