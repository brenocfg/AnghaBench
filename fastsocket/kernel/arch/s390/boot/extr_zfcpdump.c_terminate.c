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

/* Variables and functions */
 int /*<<< orphan*/  DEV_ZCORE_REIPL ; 
 int /*<<< orphan*/  LINUX_REBOOT_CMD_POWER_OFF ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  REIPL ; 
 int /*<<< orphan*/  WAIT_TIME_END ; 
 int /*<<< orphan*/  close (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reboot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void terminate(void)
{
	int fd;

	sleep(WAIT_TIME_END); /* give the messages time to be displayed */
	fd = open(DEV_ZCORE_REIPL, O_WRONLY, 0);
	if (fd == -1)
		goto no_reipl;
	write(fd, REIPL, 1);
	close(fd);
no_reipl:
	reboot(LINUX_REBOOT_CMD_POWER_OFF);
}