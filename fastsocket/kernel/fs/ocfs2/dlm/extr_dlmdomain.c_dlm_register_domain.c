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
struct dlm_protocol_version {int dummy; } ;
struct dlm_ctxt {scalar_t__ dlm_state; struct dlm_protocol_version fs_locking_proto; int /*<<< orphan*/  dlm_locking_proto; int /*<<< orphan*/  list; int /*<<< orphan*/  num_joins; } ;

/* Variables and functions */
 scalar_t__ DLM_CTXT_JOINED ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int EPROTO ; 
 int ERESTARTSYS ; 
 struct dlm_ctxt* ERR_PTR (int) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ O2NM_MAX_NAME_LEN ; 
 int /*<<< orphan*/  __dlm_get (struct dlm_ctxt*) ; 
 struct dlm_ctxt* __dlm_lookup_domain (char const*) ; 
 int /*<<< orphan*/  current ; 
 struct dlm_ctxt* dlm_alloc_ctxt (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_domain_events ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int /*<<< orphan*/  dlm_domains ; 
 int /*<<< orphan*/  dlm_free_ctxt_mem (struct dlm_ctxt*) ; 
 int dlm_join_domain (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_protocol ; 
 scalar_t__ dlm_protocol_compare (struct dlm_protocol_version*,struct dlm_protocol_version*) ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_wait_on_domain_helper (char const*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  o2hb_check_local_node_heartbeating () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dlm_ctxt * dlm_register_domain(const char *domain,
			       u32 key,
			       struct dlm_protocol_version *fs_proto)
{
	int ret;
	struct dlm_ctxt *dlm = NULL;
	struct dlm_ctxt *new_ctxt = NULL;

	if (strlen(domain) > O2NM_MAX_NAME_LEN) {
		ret = -ENAMETOOLONG;
		mlog(ML_ERROR, "domain name length too long\n");
		goto leave;
	}

	if (!o2hb_check_local_node_heartbeating()) {
		mlog(ML_ERROR, "the local node has not been configured, or is "
		     "not heartbeating\n");
		ret = -EPROTO;
		goto leave;
	}

	mlog(0, "register called for domain \"%s\"\n", domain);

retry:
	dlm = NULL;
	if (signal_pending(current)) {
		ret = -ERESTARTSYS;
		mlog_errno(ret);
		goto leave;
	}

	spin_lock(&dlm_domain_lock);

	dlm = __dlm_lookup_domain(domain);
	if (dlm) {
		if (dlm->dlm_state != DLM_CTXT_JOINED) {
			spin_unlock(&dlm_domain_lock);

			mlog(0, "This ctxt is not joined yet!\n");
			wait_event_interruptible(dlm_domain_events,
						 dlm_wait_on_domain_helper(
							 domain));
			goto retry;
		}

		if (dlm_protocol_compare(&dlm->fs_locking_proto, fs_proto)) {
			mlog(ML_ERROR,
			     "Requested locking protocol version is not "
			     "compatible with already registered domain "
			     "\"%s\"\n", domain);
			ret = -EPROTO;
			goto leave;
		}

		__dlm_get(dlm);
		dlm->num_joins++;

		spin_unlock(&dlm_domain_lock);

		ret = 0;
		goto leave;
	}

	/* doesn't exist */
	if (!new_ctxt) {
		spin_unlock(&dlm_domain_lock);

		new_ctxt = dlm_alloc_ctxt(domain, key);
		if (new_ctxt)
			goto retry;

		ret = -ENOMEM;
		mlog_errno(ret);
		goto leave;
	}

	/* a little variable switch-a-roo here... */
	dlm = new_ctxt;
	new_ctxt = NULL;

	/* add the new domain */
	list_add_tail(&dlm->list, &dlm_domains);
	spin_unlock(&dlm_domain_lock);

	/*
	 * Pass the locking protocol version into the join.  If the join
	 * succeeds, it will have the negotiated protocol set.
	 */
	dlm->dlm_locking_proto = dlm_protocol;
	dlm->fs_locking_proto = *fs_proto;

	ret = dlm_join_domain(dlm);
	if (ret) {
		mlog_errno(ret);
		dlm_put(dlm);
		goto leave;
	}

	/* Tell the caller what locking protocol we negotiated */
	*fs_proto = dlm->fs_locking_proto;

	ret = 0;
leave:
	if (new_ctxt)
		dlm_free_ctxt_mem(new_ctxt);

	if (ret < 0)
		dlm = ERR_PTR(ret);

	return dlm;
}