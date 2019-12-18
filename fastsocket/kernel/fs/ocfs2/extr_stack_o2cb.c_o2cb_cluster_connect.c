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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  pv_minor; int /*<<< orphan*/  pv_major; } ;
struct ocfs2_cluster_connection {struct o2dlm_private* cc_private; struct dlm_ctxt* cc_lockspace; TYPE_1__ cc_version; int /*<<< orphan*/  cc_name; int /*<<< orphan*/  cc_namelen; } ;
struct o2dlm_private {int /*<<< orphan*/  op_eviction_cb; } ;
struct dlm_protocol_version {int /*<<< orphan*/  pv_minor; int /*<<< orphan*/  pv_major; } ;
struct dlm_ctxt {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sp_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dlm_ctxt*) ; 
 int PTR_ERR (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dlm_ctxt* dlm_register_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_protocol_version*) ; 
 int /*<<< orphan*/  dlm_register_eviction_cb (struct dlm_ctxt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_setup_eviction_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ocfs2_cluster_connection*) ; 
 int /*<<< orphan*/  kfree (struct o2dlm_private*) ; 
 struct o2dlm_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 TYPE_2__ o2cb_stack ; 
 int /*<<< orphan*/  o2dlm_eviction_cb ; 
 int /*<<< orphan*/  o2hb_check_local_node_heartbeating () ; 

__attribute__((used)) static int o2cb_cluster_connect(struct ocfs2_cluster_connection *conn)
{
	int rc = 0;
	u32 dlm_key;
	struct dlm_ctxt *dlm;
	struct o2dlm_private *priv;
	struct dlm_protocol_version dlm_version;

	BUG_ON(conn == NULL);
	BUG_ON(o2cb_stack.sp_proto == NULL);

	/* for now we only have one cluster/node, make sure we see it
	 * in the heartbeat universe */
	if (!o2hb_check_local_node_heartbeating()) {
		rc = -EINVAL;
		goto out;
	}

	priv = kzalloc(sizeof(struct o2dlm_private), GFP_KERNEL);
	if (!priv) {
		rc = -ENOMEM;
		goto out_free;
	}

	/* This just fills the structure in.  It is safe to pass conn. */
	dlm_setup_eviction_cb(&priv->op_eviction_cb, o2dlm_eviction_cb,
			      conn);

	conn->cc_private = priv;

	/* used by the dlm code to make message headers unique, each
	 * node in this domain must agree on this. */
	dlm_key = crc32_le(0, conn->cc_name, conn->cc_namelen);
	dlm_version.pv_major = conn->cc_version.pv_major;
	dlm_version.pv_minor = conn->cc_version.pv_minor;

	dlm = dlm_register_domain(conn->cc_name, dlm_key, &dlm_version);
	if (IS_ERR(dlm)) {
		rc = PTR_ERR(dlm);
		mlog_errno(rc);
		goto out_free;
	}

	conn->cc_version.pv_major = dlm_version.pv_major;
	conn->cc_version.pv_minor = dlm_version.pv_minor;
	conn->cc_lockspace = dlm;

	dlm_register_eviction_cb(dlm, &priv->op_eviction_cb);

out_free:
	if (rc && conn->cc_private)
		kfree(conn->cc_private);

out:
	return rc;
}