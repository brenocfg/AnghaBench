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
struct kinfo_proc {scalar_t__ ki_pid; } ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ ESRCH ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getchar () ; 
 scalar_t__ interactive ; 
 int kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  show_process (struct kinfo_proc const*) ; 
 int /*<<< orphan*/  signum ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int
killact(const struct kinfo_proc *kp)
{
	int ch, first;

	if (interactive) {
		/*
		 * Be careful, ask before killing.
		 */
		printf("kill ");
		show_process(kp);
		printf("? ");
		fflush(stdout);
		first = ch = getchar();
		while (ch != '\n' && ch != EOF)
			ch = getchar();
		if (first != 'y' && first != 'Y')
			return (1);
	}
	if (kill(kp->ki_pid, signum) == -1) {
		/* 
		 * Check for ESRCH, which indicates that the process
		 * disappeared between us matching it and us
		 * signalling it; don't issue a warning about it.
		 */
		if (errno != ESRCH)
			warn("signalling pid %d", (int)kp->ki_pid);
		/*
		 * Return 0 to indicate that the process should not be
		 * considered a match, since we didn't actually get to
		 * signal it.
		 */
		return (0);
	}
	return (1);
}