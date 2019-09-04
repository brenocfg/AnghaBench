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
struct rusage {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  T_ASSERT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait4 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct rusage*) ; 

__attribute__((used)) static void
test_child_process(pid_t child_pid, int *status, struct rusage *ru)
{
	int err = 0;
	pid_t got_pid;

	T_LOG("  continuing child[%d]\n", child_pid);

	err = kill(child_pid, SIGCONT);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(err, "  kill(%d, SIGCONT) failed", child_pid);

	T_LOG("  waiting for child[%d] to exit", child_pid);

	got_pid = wait4(child_pid, status, 0, ru);
	T_QUIET; T_ASSERT_EQ(child_pid, got_pid, "  wait4(%d, ...) returned %d", child_pid, got_pid);
}