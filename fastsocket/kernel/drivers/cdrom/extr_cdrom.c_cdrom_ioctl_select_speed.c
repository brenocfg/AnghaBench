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
struct cdrom_device_info {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* select_speed ) (struct cdrom_device_info*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_SELECT_SPEED ; 
 int /*<<< orphan*/  CDROM_CAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct cdrom_device_info*,unsigned long) ; 

__attribute__((used)) static int cdrom_ioctl_select_speed(struct cdrom_device_info *cdi,
		unsigned long arg)
{
	cdinfo(CD_DO_IOCTL, "entering CDROM_SELECT_SPEED\n");

	if (!CDROM_CAN(CDC_SELECT_SPEED))
		return -ENOSYS;
	return cdi->ops->select_speed(cdi, arg);
}