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
struct lwp_info {int /*<<< orphan*/  ptid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_KILL ; 
 scalar_t__ debug_lin_lwp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kill_callback (struct lwp_info *lp, void *data)
{
  errno = 0;
  ptrace (PTRACE_KILL, GET_LWP (lp->ptid), 0, 0);
  if (debug_lin_lwp)
    fprintf_unfiltered (gdb_stdlog,
			"KC:  PTRACE_KILL %s, 0, 0 (%s)\n",
			target_pid_to_str (lp->ptid),
			errno ? safe_strerror (errno) : "OK");

  return 0;
}