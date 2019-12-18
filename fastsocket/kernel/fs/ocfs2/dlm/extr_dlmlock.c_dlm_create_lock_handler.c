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
typedef  int /*<<< orphan*/  u32 ;
struct o2net_msg {scalar_t__ buf; } ;
struct dlm_lockstatus {int /*<<< orphan*/  flags; } ;
struct dlm_lock_resource {int /*<<< orphan*/  spinlock; } ;
struct dlm_lock {struct dlm_lockstatus* lksb; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; } ;
struct dlm_create_lock {char* name; unsigned int namelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  cookie; int /*<<< orphan*/  node_idx; int /*<<< orphan*/  requested_type; } ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_IVBUFLEN ; 
 int DLM_IVLOCKID ; 
 int /*<<< orphan*/  DLM_LKSB_GET_LVB ; 
 unsigned int DLM_LOCKID_NAME_MAX ; 
 int DLM_NORMAL ; 
 int DLM_REJECTED ; 
 int DLM_SYSERR ; 
 int LKM_GET_LVB ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int __dlm_lockres_state_to_status (struct dlm_lock_resource*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_domain_fully_joined (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_error (int) ; 
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_lock_attach_lockres (struct dlm_lock*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lock_put (struct dlm_lock*) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 struct dlm_lock_resource* dlm_lookup_lockres (struct dlm_ctxt*,char*,unsigned int) ; 
 struct dlm_lock* dlm_new_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int dlmlock_master (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_lock*,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_create_lock_handler(struct o2net_msg *msg, u32 len, void *data,
			    void **ret_data)
{
	struct dlm_ctxt *dlm = data;
	struct dlm_create_lock *create = (struct dlm_create_lock *)msg->buf;
	struct dlm_lock_resource *res = NULL;
	struct dlm_lock *newlock = NULL;
	struct dlm_lockstatus *lksb = NULL;
	enum dlm_status status = DLM_NORMAL;
	char *name;
	unsigned int namelen;

	BUG_ON(!dlm);

	mlog_entry_void();

	if (!dlm_grab(dlm))
		return DLM_REJECTED;

	name = create->name;
	namelen = create->namelen;
	status = DLM_REJECTED;
	if (!dlm_domain_fully_joined(dlm)) {
		mlog(ML_ERROR, "Domain %s not fully joined, but node %u is "
		     "sending a create_lock message for lock %.*s!\n",
		     dlm->name, create->node_idx, namelen, name);
		dlm_error(status);
		goto leave;
	}

	status = DLM_IVBUFLEN;
	if (namelen > DLM_LOCKID_NAME_MAX) {
		dlm_error(status);
		goto leave;
	}

	status = DLM_SYSERR;
	newlock = dlm_new_lock(create->requested_type,
			       create->node_idx,
			       be64_to_cpu(create->cookie), NULL);
	if (!newlock) {
		dlm_error(status);
		goto leave;
	}

	lksb = newlock->lksb;

	if (be32_to_cpu(create->flags) & LKM_GET_LVB) {
		lksb->flags |= DLM_LKSB_GET_LVB;
		mlog(0, "set DLM_LKSB_GET_LVB flag\n");
	}

	status = DLM_IVLOCKID;
	res = dlm_lookup_lockres(dlm, name, namelen);
	if (!res) {
		dlm_error(status);
		goto leave;
	}

	spin_lock(&res->spinlock);
	status = __dlm_lockres_state_to_status(res);
	spin_unlock(&res->spinlock);

	if (status != DLM_NORMAL) {
		mlog(0, "lockres recovering/migrating/in-progress\n");
		goto leave;
	}

	dlm_lock_attach_lockres(newlock, res);

	status = dlmlock_master(dlm, res, newlock, be32_to_cpu(create->flags));
leave:
	if (status != DLM_NORMAL)
		if (newlock)
			dlm_lock_put(newlock);

	if (res)
		dlm_lockres_put(res);

	dlm_put(dlm);

	return status;
}