#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parm_part; } ;

/* Variables and functions */
 char* DEV_SCSI ; 
 int /*<<< orphan*/  DUMP_DIR ; 
 int /*<<< orphan*/  PRINT_PERR (char*) ; 
 int /*<<< orphan*/  PRINT_TRACE (char*) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 TYPE_1__ g ; 
 scalar_t__ mount (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_dump_device(void)
{
	int pid;
	char dump_part[16];

	PRINT_TRACE("e2fsck\n");
	sprintf(dump_part, "%s%i", DEV_SCSI, atoi(g.parm_part));

	pid = fork();
	if (pid < 0) {
		PRINT_PERR("fork failed\n");
		return -1;
	} else if (pid == 0) {
		execl("/bin/e2fsck", "e2fsck", dump_part, "-y", NULL);
		execl("/sbin/e2fsck", "e2fsck", dump_part, "-y", NULL);
		exit(1);
	} else {
		waitpid(pid, NULL, 0);
	}

	PRINT_TRACE("mount\n");
	if (mount(dump_part, DUMP_DIR, "ext4", 0, NULL) == 0)
		return 0;
	if (mount(dump_part, DUMP_DIR, "ext3", 0, NULL) == 0)
		return 0;
	if (mount(dump_part, DUMP_DIR, "ext2", 0, NULL) != 0) {
		PRINT_PERR("mount failed\n");
		return -1;
	}
	return 0;
}