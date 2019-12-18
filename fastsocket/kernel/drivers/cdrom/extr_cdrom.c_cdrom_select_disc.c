#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cdrom_device_info {int mc_flags; int use_count; TYPE_2__* ops; } ;
struct TYPE_3__ {int curslot; } ;
struct cdrom_changer_info {TYPE_1__ hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* media_changed ) (struct cdrom_device_info*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_SELECT_DISC ; 
 int /*<<< orphan*/  CDROM_CAN (int /*<<< orphan*/ ) ; 
 int CDSL_CURRENT ; 
 int CDSL_NONE ; 
 int /*<<< orphan*/  CD_CHANGER ; 
 int EBUSY ; 
 int EDRIVE_CANT_DO_THIS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*) ; 
 int cdrom_load_unload (struct cdrom_device_info*,int) ; 
 int cdrom_read_mech_status (struct cdrom_device_info*,struct cdrom_changer_info*) ; 
 scalar_t__ keeplocked ; 
 int /*<<< orphan*/  kfree (struct cdrom_changer_info*) ; 
 struct cdrom_changer_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cdrom_device_info*,int) ; 

__attribute__((used)) static int cdrom_select_disc(struct cdrom_device_info *cdi, int slot)
{
	struct cdrom_changer_info *info;
	int curslot;
	int ret;

	cdinfo(CD_CHANGER, "entering cdrom_select_disc()\n"); 
	if (!CDROM_CAN(CDC_SELECT_DISC))
		return -EDRIVE_CANT_DO_THIS;

	(void) cdi->ops->media_changed(cdi, slot);

	if (slot == CDSL_NONE) {
		/* set media changed bits, on both queues */
		cdi->mc_flags = 0x3;
		return cdrom_load_unload(cdi, -1);
	}

	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	if ((ret = cdrom_read_mech_status(cdi, info))) {
		kfree(info);
		return ret;
	}

	curslot = info->hdr.curslot;
	kfree(info);

	if (cdi->use_count > 1 || keeplocked) {
		if (slot == CDSL_CURRENT) {
	    		return curslot;
		} else {
			return -EBUSY;
		}
	}

	/* Specifying CDSL_CURRENT will attempt to load the currnet slot,
	which is useful if it had been previously unloaded.
	Whether it can or not, it returns the current slot. 
	Similarly,  if slot happens to be the current one, we still
	try and load it. */
	if (slot == CDSL_CURRENT)
		slot = curslot;

	/* set media changed bits on both queues */
	cdi->mc_flags = 0x3;
	if ((ret = cdrom_load_unload(cdi, slot)))
		return ret;

	return slot;
}