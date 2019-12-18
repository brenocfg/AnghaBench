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
typedef  int /*<<< orphan*/  unlock ;
typedef  scalar_t__ u8 ;
struct kvec {int iov_len; struct dlm_unlock_lock* iov_base; } ;
struct dlm_unlock_lock {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  cookie; int /*<<< orphan*/  flags; scalar_t__ node_idx; } ;
struct dlm_lockstatus {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {TYPE_2__ lockname; } ;
struct TYPE_4__ {int /*<<< orphan*/  cookie; } ;
struct dlm_lock {TYPE_3__* lksb; TYPE_1__ ml; } ;
struct dlm_ctxt {int /*<<< orphan*/  key; scalar_t__ node_num; int /*<<< orphan*/  name; } ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;
struct TYPE_6__ {struct dlm_unlock_lock* lvb; } ;

/* Variables and functions */
 int DLM_FORWARD ; 
 int DLM_LVB_LEN ; 
 int DLM_NORMAL ; 
 int /*<<< orphan*/  DLM_UNLOCK_LOCK_MSG ; 
 int LKM_PUT_LVB ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int dlm_err_to_dlm_status (int) ; 
 scalar_t__ dlm_is_host_down (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dlm_unlock_lock*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvec*,size_t,scalar_t__,int*) ; 

__attribute__((used)) static enum dlm_status dlm_send_remote_unlock_request(struct dlm_ctxt *dlm,
						 struct dlm_lock_resource *res,
						 struct dlm_lock *lock,
						 struct dlm_lockstatus *lksb,
						 int flags,
						 u8 owner)
{
	struct dlm_unlock_lock unlock;
	int tmpret;
	enum dlm_status ret;
	int status = 0;
	struct kvec vec[2];
	size_t veclen = 1;

	mlog_entry("%.*s\n", res->lockname.len, res->lockname.name);

	if (owner == dlm->node_num) {
		/* ended up trying to contact ourself.  this means
		 * that the lockres had been remote but became local
		 * via a migration.  just retry it, now as local */
		mlog(0, "%s:%.*s: this node became the master due to a "
		     "migration, re-evaluate now\n", dlm->name,
		     res->lockname.len, res->lockname.name);
		return DLM_FORWARD;
	}

	memset(&unlock, 0, sizeof(unlock));
	unlock.node_idx = dlm->node_num;
	unlock.flags = cpu_to_be32(flags);
	unlock.cookie = lock->ml.cookie;
	unlock.namelen = res->lockname.len;
	memcpy(unlock.name, res->lockname.name, unlock.namelen);

	vec[0].iov_len = sizeof(struct dlm_unlock_lock);
	vec[0].iov_base = &unlock;

	if (flags & LKM_PUT_LVB) {
		/* extra data to send if we are updating lvb */
		vec[1].iov_len = DLM_LVB_LEN;
		vec[1].iov_base = lock->lksb->lvb;
		veclen++;
	}

	tmpret = o2net_send_message_vec(DLM_UNLOCK_LOCK_MSG, dlm->key,
					vec, veclen, owner, &status);
	if (tmpret >= 0) {
		// successfully sent and received
		if (status == DLM_FORWARD)
			mlog(0, "master was in-progress.  retry\n");
		ret = status;
	} else {
		mlog_errno(tmpret);
		if (dlm_is_host_down(tmpret)) {
			/* NOTE: this seems strange, but it is what we want.
			 * when the master goes down during a cancel or
			 * unlock, the recovery code completes the operation
			 * as if the master had not died, then passes the
			 * updated state to the recovery master.  this thread
			 * just needs to finish out the operation and call
			 * the unlockast. */
			ret = DLM_NORMAL;
		} else {
			/* something bad.  this will BUG in ocfs2 */
			ret = dlm_err_to_dlm_status(tmpret);
		}
	}

	return ret;
}