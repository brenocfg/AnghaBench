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
struct dasd_uid {int dummy; } ;
struct dasd_eckd_private {struct alias_server* lcu; } ;
struct dasd_device {int /*<<< orphan*/  alias_list; TYPE_1__* discipline; scalar_t__ private; } ;
struct alias_server {int /*<<< orphan*/  lock; int /*<<< orphan*/  inactive_devices; int /*<<< orphan*/  lculist; int /*<<< orphan*/  lcu; int /*<<< orphan*/  server; } ;
struct alias_lcu {int /*<<< orphan*/  lock; int /*<<< orphan*/  inactive_devices; int /*<<< orphan*/  lculist; int /*<<< orphan*/  lcu; int /*<<< orphan*/  server; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  serverlist; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_uid ) (struct dasd_device*,struct dasd_uid*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct alias_server*) ; 
 int PTR_ERR (struct alias_server*) ; 
 struct alias_server* _allocate_lcu (struct dasd_uid*) ; 
 struct alias_server* _allocate_server (struct dasd_uid*) ; 
 struct alias_server* _find_lcu (struct alias_server*,struct dasd_uid*) ; 
 struct alias_server* _find_server (struct dasd_uid*) ; 
 int /*<<< orphan*/  _free_lcu (struct alias_server*) ; 
 int /*<<< orphan*/  _free_server (struct alias_server*) ; 
 TYPE_2__ aliastree ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*,struct dasd_uid*) ; 

int dasd_alias_make_device_known_to_lcu(struct dasd_device *device)
{
	struct dasd_eckd_private *private;
	unsigned long flags;
	struct alias_server *server, *newserver;
	struct alias_lcu *lcu, *newlcu;
	struct dasd_uid uid;

	private = (struct dasd_eckd_private *) device->private;

	device->discipline->get_uid(device, &uid);
	spin_lock_irqsave(&aliastree.lock, flags);
	server = _find_server(&uid);
	if (!server) {
		spin_unlock_irqrestore(&aliastree.lock, flags);
		newserver = _allocate_server(&uid);
		if (IS_ERR(newserver))
			return PTR_ERR(newserver);
		spin_lock_irqsave(&aliastree.lock, flags);
		server = _find_server(&uid);
		if (!server) {
			list_add(&newserver->server, &aliastree.serverlist);
			server = newserver;
		} else {
			/* someone was faster */
			_free_server(newserver);
		}
	}

	lcu = _find_lcu(server, &uid);
	if (!lcu) {
		spin_unlock_irqrestore(&aliastree.lock, flags);
		newlcu = _allocate_lcu(&uid);
		if (IS_ERR(newlcu))
			return PTR_ERR(lcu);
		spin_lock_irqsave(&aliastree.lock, flags);
		lcu = _find_lcu(server, &uid);
		if (!lcu) {
			list_add(&newlcu->lcu, &server->lculist);
			lcu = newlcu;
		} else {
			/* someone was faster */
			_free_lcu(newlcu);
		}
	}
	spin_lock(&lcu->lock);
	list_add(&device->alias_list, &lcu->inactive_devices);
	private->lcu = lcu;
	spin_unlock(&lcu->lock);
	spin_unlock_irqrestore(&aliastree.lock, flags);

	return 0;
}