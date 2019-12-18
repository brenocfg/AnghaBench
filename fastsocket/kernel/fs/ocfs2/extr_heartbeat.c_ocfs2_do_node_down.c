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
struct ocfs2_super {int node_num; int /*<<< orphan*/  cconn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ocfs2_recovery_thread (struct ocfs2_super*,int) ; 

void ocfs2_do_node_down(int node_num, void *data)
{
	struct ocfs2_super *osb = data;

	BUG_ON(osb->node_num == node_num);

	mlog(0, "ocfs2: node down event for %d\n", node_num);

	if (!osb->cconn) {
		/*
		 * No cluster connection means we're not even ready to
		 * participate yet.  We check the slots after the cluster
		 * comes up, so we will notice the node death then.  We
		 * can safely ignore it here.
		 */
		return;
	}

	ocfs2_recovery_thread(osb, node_num);
}