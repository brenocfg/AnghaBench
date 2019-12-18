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
struct cdrom_device_info {unsigned int capacity; } ;
struct cdrom_changer_info {TYPE_1__* slots; } ;
struct TYPE_2__ {int change; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_MEDIA_CHANGED ; 
 int /*<<< orphan*/  CDC_SELECT_DISC ; 
 int /*<<< orphan*/  CDROM_CAN (int /*<<< orphan*/ ) ; 
 unsigned long CDSL_CURRENT ; 
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*) ; 
 int cdrom_read_mech_status (struct cdrom_device_info*,struct cdrom_changer_info*) ; 
 int /*<<< orphan*/  kfree (struct cdrom_changer_info*) ; 
 struct cdrom_changer_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int media_changed (struct cdrom_device_info*,int) ; 

__attribute__((used)) static int cdrom_ioctl_media_changed(struct cdrom_device_info *cdi,
		unsigned long arg)
{
	struct cdrom_changer_info *info;
	int ret;

	cdinfo(CD_DO_IOCTL, "entering CDROM_MEDIA_CHANGED\n");

	if (!CDROM_CAN(CDC_MEDIA_CHANGED))
		return -ENOSYS;

	/* cannot select disc or select current disc */
	if (!CDROM_CAN(CDC_SELECT_DISC) || arg == CDSL_CURRENT)
		return media_changed(cdi, 1);

	if ((unsigned int)arg >= cdi->capacity)
		return -EINVAL;

	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	ret = cdrom_read_mech_status(cdi, info);
	if (!ret)
		ret = info->slots[arg].change;
	kfree(info);
	return ret;
}