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

/* Variables and functions */
 int /*<<< orphan*/  PRINT_PERR (char*) ; 
 int /*<<< orphan*/  execl (char*,char*,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void modprobe(const char *module)
{
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		PRINT_PERR("fork failed\n");
		return;
	} else if (pid == 0) {
		execl("/bin/modprobe", "modprobe", module, "-q", NULL);
		execl("/sbin/modprobe", "modprobe", module, "-q", NULL);
		exit(1);
	} else {
		waitpid(pid, NULL, 0);
	}
}