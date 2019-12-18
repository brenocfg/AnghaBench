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
struct cdrom_device_info {scalar_t__ sanyo_slot; } ;
struct cdrom_changer_info {TYPE_1__* slots; } ;
struct TYPE_2__ {scalar_t__ disc_present; } ;

/* Variables and functions */
 int CDS_DISC_OK ; 
 int CDS_NO_DISC ; 
 int CDS_NO_INFO ; 
 int /*<<< orphan*/  CD_CHANGER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*) ; 
 int cdrom_read_mech_status (struct cdrom_device_info*,struct cdrom_changer_info*) ; 
 int /*<<< orphan*/  kfree (struct cdrom_changer_info*) ; 
 struct cdrom_changer_info* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdrom_slot_status(struct cdrom_device_info *cdi, int slot)
{
	struct cdrom_changer_info *info;
	int ret;

	cdinfo(CD_CHANGER, "entering cdrom_slot_status()\n"); 
	if (cdi->sanyo_slot)
		return CDS_NO_INFO;
	
	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	if ((ret = cdrom_read_mech_status(cdi, info)))
		goto out_free;

	if (info->slots[slot].disc_present)
		ret = CDS_DISC_OK;
	else
		ret = CDS_NO_DISC;

out_free:
	kfree(info);
	return ret;
}