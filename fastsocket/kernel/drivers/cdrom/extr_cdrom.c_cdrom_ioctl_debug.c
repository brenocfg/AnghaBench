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
struct cdrom_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int EACCES ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*,char*) ; 
 int debug ; 

__attribute__((used)) static int cdrom_ioctl_debug(struct cdrom_device_info *cdi,
		unsigned long arg)
{
	cdinfo(CD_DO_IOCTL, "%sabling debug.\n", arg ? "En" : "Dis");

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;
	debug = arg ? 1 : 0;
	return debug;
}