#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dasd_uid {int dummy; } ;
struct dasd_eckd_private {struct alias_lcu* lcu; } ;
struct dasd_device {int /*<<< orphan*/  alias_list; TYPE_1__* discipline; scalar_t__ private; } ;
struct alias_server {int /*<<< orphan*/  server; int /*<<< orphan*/  lculist; } ;
struct TYPE_7__ {struct dasd_device* device; int /*<<< orphan*/  dwork; } ;
struct TYPE_6__ {struct dasd_device* device; int /*<<< orphan*/  worker; } ;
struct alias_lcu {int /*<<< orphan*/  lock; int /*<<< orphan*/  lcu; int /*<<< orphan*/  inactive_devices; int /*<<< orphan*/  active_devices; int /*<<< orphan*/  grouplist; TYPE_3__ ruac_data; TYPE_2__ suc_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_uid ) (struct dasd_device*,struct dasd_uid*) ;} ;

/* Variables and functions */
 struct alias_server* _find_server (struct dasd_uid*) ; 
 int /*<<< orphan*/  _free_lcu (struct alias_lcu*) ; 
 int /*<<< orphan*/  _free_server (struct alias_server*) ; 
 int /*<<< orphan*/  _schedule_lcu_update (struct alias_lcu*,int /*<<< orphan*/ *) ; 
 TYPE_4__ aliastree ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*,struct dasd_uid*) ; 

void dasd_alias_disconnect_device_from_lcu(struct dasd_device *device)
{
	struct dasd_eckd_private *private;
	unsigned long flags;
	struct alias_lcu *lcu;
	struct alias_server *server;
	int was_pending;
	struct dasd_uid uid;

	private = (struct dasd_eckd_private *) device->private;
	lcu = private->lcu;
	/* nothing to do if already disconnected */
	if (!lcu)
		return;
	device->discipline->get_uid(device, &uid);
	spin_lock_irqsave(&lcu->lock, flags);
	list_del_init(&device->alias_list);
	/* make sure that the workers don't use this device */
	if (device == lcu->suc_data.device) {
		spin_unlock_irqrestore(&lcu->lock, flags);
		cancel_work_sync(&lcu->suc_data.worker);
		spin_lock_irqsave(&lcu->lock, flags);
		if (device == lcu->suc_data.device)
			lcu->suc_data.device = NULL;
	}
	was_pending = 0;
	if (device == lcu->ruac_data.device) {
		spin_unlock_irqrestore(&lcu->lock, flags);
		was_pending = 1;
		cancel_delayed_work_sync(&lcu->ruac_data.dwork);
		spin_lock_irqsave(&lcu->lock, flags);
		if (device == lcu->ruac_data.device)
			lcu->ruac_data.device = NULL;
	}
	private->lcu = NULL;
	spin_unlock_irqrestore(&lcu->lock, flags);

	spin_lock_irqsave(&aliastree.lock, flags);
	spin_lock(&lcu->lock);
	if (list_empty(&lcu->grouplist) &&
	    list_empty(&lcu->active_devices) &&
	    list_empty(&lcu->inactive_devices)) {
		list_del(&lcu->lcu);
		spin_unlock(&lcu->lock);
		_free_lcu(lcu);
		lcu = NULL;
	} else {
		if (was_pending)
			_schedule_lcu_update(lcu, NULL);
		spin_unlock(&lcu->lock);
	}
	server = _find_server(&uid);
	if (server && list_empty(&server->lculist)) {
		list_del(&server->server);
		_free_server(server);
	}
	spin_unlock_irqrestore(&aliastree.lock, flags);
}