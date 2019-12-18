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
struct kinfo_proc {char* ki_comm; scalar_t__ ki_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kd ; 
 char** kvm_getargv (int /*<<< orphan*/ ,struct kinfo_proc const*,int /*<<< orphan*/ ) ; 
 scalar_t__ longfmt ; 
 scalar_t__ matchargs ; 
 int /*<<< orphan*/  pgrep ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ quiet ; 

__attribute__((used)) static void
show_process(const struct kinfo_proc *kp)
{
	char **argv;

	if (quiet) {
		assert(pgrep);
		return;
	}
	if ((longfmt || !pgrep) && matchargs &&
	    (argv = kvm_getargv(kd, kp, 0)) != NULL) {
		printf("%d ", (int)kp->ki_pid);
		for (; *argv != NULL; argv++) {
			printf("%s", *argv);
			if (argv[1] != NULL)
				putchar(' ');
		}
	} else if (longfmt || !pgrep)
		printf("%d %s", (int)kp->ki_pid, kp->ki_comm);
	else
		printf("%d", (int)kp->ki_pid);
}