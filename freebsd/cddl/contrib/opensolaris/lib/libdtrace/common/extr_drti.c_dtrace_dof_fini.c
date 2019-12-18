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
 int /*<<< orphan*/  DTRACEHIOC_REMOVE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dbg_printf (int,char*,int) ; 
 int devnamep ; 
 int gen ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open64 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_dof_fini(void)
{
	int fd;

	if ((fd = open64(devnamep, O_RDWR)) < 0) {
		dbg_printf(1, "failed to open helper device %s", devnamep);
		return;
	}

	if ((gen = ioctl(fd, DTRACEHIOC_REMOVE, &gen)) == -1)
		dbg_printf(1, "DTrace ioctl failed to remove DOF (%d)\n", gen);
	else
		dbg_printf(1, "DTrace ioctl removed DOF (%d)\n", gen);

	(void) close(fd);
}