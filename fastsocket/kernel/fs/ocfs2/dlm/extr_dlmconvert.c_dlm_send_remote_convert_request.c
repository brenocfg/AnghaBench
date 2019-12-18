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
struct kvec {int iov_len; struct dlm_convert_lock* iov_base; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int /*<<< orphan*/  owner; TYPE_2__ lockname; } ;
struct TYPE_4__ {int /*<<< orphan*/  cookie; } ;
struct dlm_lock {TYPE_3__* lksb; TYPE_1__ ml; } ;
struct dlm_ctxt {int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; } ;
struct dlm_convert_lock {int requested_type; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  cookie; int /*<<< orphan*/  node_idx; } ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;
struct TYPE_6__ {struct dlm_convert_lock* lvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_CONVERT_LOCK_MSG ; 
 int DLM_FORWARD ; 
 int DLM_LVB_LEN ; 
 int DLM_MIGRATING ; 
 int /*<<< orphan*/  DLM_NODE_DEATH_WAIT_MAX ; 
 int DLM_NORMAL ; 
 int DLM_NOTQUEUED ; 
 int DLM_RECOVERING ; 
 int LKM_PUT_LVB ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int dlm_err_to_dlm_status (int) ; 
 int /*<<< orphan*/  dlm_error (int) ; 
 scalar_t__ dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_wait_for_node_death (struct dlm_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dlm_convert_lock*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvec*,size_t,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static enum dlm_status dlm_send_remote_convert_request(struct dlm_ctxt *dlm,
					   struct dlm_lock_resource *res,
					   struct dlm_lock *lock, int flags, int type)
{
	struct dlm_convert_lock convert;
	int tmpret;
	enum dlm_status ret;
	int status = 0;
	struct kvec vec[2];
	size_t veclen = 1;

	mlog_entry("%.*s\n", res->lockname.len, res->lockname.name);

	memset(&convert, 0, sizeof(struct dlm_convert_lock));
	convert.node_idx = dlm->node_num;
	convert.requested_type = type;
	convert.cookie = lock->ml.cookie;
	convert.namelen = res->lockname.len;
	convert.flags = cpu_to_be32(flags);
	memcpy(convert.name, res->lockname.name, convert.namelen);

	vec[0].iov_len = sizeof(struct dlm_convert_lock);
	vec[0].iov_base = &convert;

	if (flags & LKM_PUT_LVB) {
		/* extra data to send if we are updating lvb */
		vec[1].iov_len = DLM_LVB_LEN;
		vec[1].iov_base = lock->lksb->lvb;
		veclen++;
	}

	tmpret = o2net_send_message_vec(DLM_CONVERT_LOCK_MSG, dlm->key,
					vec, veclen, res->owner, &status);
	if (tmpret >= 0) {
		// successfully sent and received
		ret = status;  // this is already a dlm_status
		if (ret == DLM_RECOVERING) {
			mlog(0, "node %u returned DLM_RECOVERING from convert "
			     "message!\n", res->owner);
		} else if (ret == DLM_MIGRATING) {
			mlog(0, "node %u returned DLM_MIGRATING from convert "
			     "message!\n", res->owner);
		} else if (ret == DLM_FORWARD) {
			mlog(0, "node %u returned DLM_FORWARD from convert "
			     "message!\n", res->owner);
		} else if (ret != DLM_NORMAL && ret != DLM_NOTQUEUED)
			dlm_error(ret);
	} else {
		mlog_errno(tmpret);
		if (dlm_is_host_down(tmpret)) {
			/* instead of logging the same network error over
			 * and over, sleep here and wait for the heartbeat
			 * to notice the node is dead.  times out after 5s. */
			dlm_wait_for_node_death(dlm, res->owner, 
						DLM_NODE_DEATH_WAIT_MAX);
			ret = DLM_RECOVERING;
			mlog(0, "node %u died so returning DLM_RECOVERING "
			     "from convert message!\n", res->owner);
		} else {
			ret = dlm_err_to_dlm_status(tmpret);
		}
	}

	return ret;
}