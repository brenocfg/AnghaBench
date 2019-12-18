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
struct ocfs2_cluster_connection {int cc_namelen; void (* cc_recovery_handler ) (int,void*) ;int /*<<< orphan*/  cc_version; void* cc_recovery_data; int /*<<< orphan*/  cc_name; } ;
struct TYPE_6__ {TYPE_1__* sp_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  lp_max_version; } ;
struct TYPE_4__ {int (* connect ) (struct ocfs2_cluster_connection*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GROUP_NAME_MAX ; 
 TYPE_3__* active_stack ; 
 int /*<<< orphan*/  kfree (struct ocfs2_cluster_connection*) ; 
 struct ocfs2_cluster_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* lproto ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int ocfs2_stack_driver_get (char const*) ; 
 int /*<<< orphan*/  ocfs2_stack_driver_put () ; 
 int stub1 (struct ocfs2_cluster_connection*) ; 

int ocfs2_cluster_connect(const char *stack_name,
			  const char *group,
			  int grouplen,
			  void (*recovery_handler)(int node_num,
						   void *recovery_data),
			  void *recovery_data,
			  struct ocfs2_cluster_connection **conn)
{
	int rc = 0;
	struct ocfs2_cluster_connection *new_conn;

	BUG_ON(group == NULL);
	BUG_ON(conn == NULL);
	BUG_ON(recovery_handler == NULL);

	if (grouplen > GROUP_NAME_MAX) {
		rc = -EINVAL;
		goto out;
	}

	new_conn = kzalloc(sizeof(struct ocfs2_cluster_connection),
			   GFP_KERNEL);
	if (!new_conn) {
		rc = -ENOMEM;
		goto out;
	}

	memcpy(new_conn->cc_name, group, grouplen);
	new_conn->cc_namelen = grouplen;
	new_conn->cc_recovery_handler = recovery_handler;
	new_conn->cc_recovery_data = recovery_data;

	/* Start the new connection at our maximum compatibility level */
	new_conn->cc_version = lproto->lp_max_version;

	/* This will pin the stack driver if successful */
	rc = ocfs2_stack_driver_get(stack_name);
	if (rc)
		goto out_free;

	rc = active_stack->sp_ops->connect(new_conn);
	if (rc) {
		ocfs2_stack_driver_put();
		goto out_free;
	}

	*conn = new_conn;

out_free:
	if (rc)
		kfree(new_conn);

out:
	return rc;
}