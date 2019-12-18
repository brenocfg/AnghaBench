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
struct TYPE_2__ {scalar_t__ ippathid; int /*<<< orphan*/  ipflags1; int /*<<< orphan*/  ipmsglim; int /*<<< orphan*/  ipuser; int /*<<< orphan*/  iptarget; int /*<<< orphan*/  ipvmid; } ;
union iucv_param {TYPE_1__ ctrl; } ;
typedef  int /*<<< orphan*/  u8 ;
struct iucv_path {size_t pathid; int /*<<< orphan*/  list; void* private; struct iucv_handler* handler; int /*<<< orphan*/  flags; int /*<<< orphan*/  msglim; } ;
struct iucv_handler {int /*<<< orphan*/  paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EBC_TOUPPER (int /*<<< orphan*/ ,int) ; 
 int EIO ; 
 int /*<<< orphan*/  IUCV_CONNECT ; 
 scalar_t__ cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 int /*<<< orphan*/  iucv_cleanup_queue () ; 
 int /*<<< orphan*/  iucv_error_pathid ; 
 scalar_t__ iucv_max_pathid ; 
 union iucv_param** iucv_param ; 
 struct iucv_path** iucv_path_table ; 
 int /*<<< orphan*/  iucv_sever_pathid (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_table_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iucv_path_connect(struct iucv_path *path, struct iucv_handler *handler,
		      u8 userid[8], u8 system[8], u8 userdata[16],
		      void *private)
{
	union iucv_param *parm;
	int rc;

	spin_lock_bh(&iucv_table_lock);
	iucv_cleanup_queue();
	if (cpus_empty(iucv_buffer_cpumask)) {
		rc = -EIO;
		goto out;
	}
	parm = iucv_param[smp_processor_id()];
	memset(parm, 0, sizeof(union iucv_param));
	parm->ctrl.ipmsglim = path->msglim;
	parm->ctrl.ipflags1 = path->flags;
	if (userid) {
		memcpy(parm->ctrl.ipvmid, userid, sizeof(parm->ctrl.ipvmid));
		ASCEBC(parm->ctrl.ipvmid, sizeof(parm->ctrl.ipvmid));
		EBC_TOUPPER(parm->ctrl.ipvmid, sizeof(parm->ctrl.ipvmid));
	}
	if (system) {
		memcpy(parm->ctrl.iptarget, system,
		       sizeof(parm->ctrl.iptarget));
		ASCEBC(parm->ctrl.iptarget, sizeof(parm->ctrl.iptarget));
		EBC_TOUPPER(parm->ctrl.iptarget, sizeof(parm->ctrl.iptarget));
	}
	if (userdata)
		memcpy(parm->ctrl.ipuser, userdata, sizeof(parm->ctrl.ipuser));

	rc = iucv_call_b2f0(IUCV_CONNECT, parm);
	if (!rc) {
		if (parm->ctrl.ippathid < iucv_max_pathid) {
			path->pathid = parm->ctrl.ippathid;
			path->msglim = parm->ctrl.ipmsglim;
			path->flags = parm->ctrl.ipflags1;
			path->handler = handler;
			path->private = private;
			list_add_tail(&path->list, &handler->paths);
			iucv_path_table[path->pathid] = path;
		} else {
			iucv_sever_pathid(parm->ctrl.ippathid,
					  iucv_error_pathid);
			rc = -EIO;
		}
	}
out:
	spin_unlock_bh(&iucv_table_lock);
	return rc;
}