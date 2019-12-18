#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dasd_uid {scalar_t__ type; size_t real_unit_addr; size_t base_unit_addr; int /*<<< orphan*/  vduit; int /*<<< orphan*/  ssid; int /*<<< orphan*/  serial; int /*<<< orphan*/  vendor; } ;
struct dasd_eckd_private {struct alias_pav_group* pavgroup; struct dasd_uid uid; } ;
struct dasd_device {int /*<<< orphan*/  alias_list; int /*<<< orphan*/  cdev; scalar_t__ private; } ;
struct TYPE_6__ {size_t base_unit_addr; int /*<<< orphan*/  vduit; int /*<<< orphan*/  ssid; int /*<<< orphan*/  serial; int /*<<< orphan*/  vendor; } ;
struct alias_pav_group {int /*<<< orphan*/  aliaslist; int /*<<< orphan*/  baselist; int /*<<< orphan*/  group; TYPE_3__ uid; } ;
struct alias_lcu {scalar_t__ pav; int /*<<< orphan*/  grouplist; int /*<<< orphan*/  active_devices; TYPE_2__* uac; } ;
struct TYPE_5__ {TYPE_1__* unit; } ;
struct TYPE_4__ {scalar_t__ ua_type; size_t base_ua; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_NESTED_SECOND ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NO_PAV ; 
 scalar_t__ UA_BASE_DEVICE ; 
 struct alias_pav_group* _find_group (struct alias_lcu*,struct dasd_uid*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 struct alias_pav_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int _add_device_to_lcu(struct alias_lcu *lcu,
			      struct dasd_device *device,
			      struct dasd_device *pos)
{

	struct dasd_eckd_private *private;
	struct alias_pav_group *group;
	struct dasd_uid uid;
	unsigned long flags;

	private = (struct dasd_eckd_private *) device->private;

	/* only lock if not already locked */
	if (device != pos)
		spin_lock_irqsave_nested(get_ccwdev_lock(device->cdev), flags,
					 CDEV_NESTED_SECOND);
	private->uid.type = lcu->uac->unit[private->uid.real_unit_addr].ua_type;
	private->uid.base_unit_addr =
		lcu->uac->unit[private->uid.real_unit_addr].base_ua;
	uid = private->uid;

	if (device != pos)
		spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);

	/* if we have no PAV anyway, we don't need to bother with PAV groups */
	if (lcu->pav == NO_PAV) {
		list_move(&device->alias_list, &lcu->active_devices);
		return 0;
	}

	group = _find_group(lcu, &uid);
	if (!group) {
		group = kzalloc(sizeof(*group), GFP_ATOMIC);
		if (!group)
			return -ENOMEM;
		memcpy(group->uid.vendor, uid.vendor, sizeof(uid.vendor));
		memcpy(group->uid.serial, uid.serial, sizeof(uid.serial));
		group->uid.ssid = uid.ssid;
		if (uid.type == UA_BASE_DEVICE)
			group->uid.base_unit_addr = uid.real_unit_addr;
		else
			group->uid.base_unit_addr = uid.base_unit_addr;
		memcpy(group->uid.vduit, uid.vduit, sizeof(uid.vduit));
		INIT_LIST_HEAD(&group->group);
		INIT_LIST_HEAD(&group->baselist);
		INIT_LIST_HEAD(&group->aliaslist);
		list_add(&group->group, &lcu->grouplist);
	}
	if (uid.type == UA_BASE_DEVICE)
		list_move(&device->alias_list, &group->baselist);
	else
		list_move(&device->alias_list, &group->aliaslist);
	private->pavgroup = group;
	return 0;
}