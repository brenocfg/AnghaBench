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
struct ocfs2_cluster_connection {int /*<<< orphan*/  cc_recovery_data; int /*<<< orphan*/  (* cc_recovery_handler ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cc_name; int /*<<< orphan*/  cc_namelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void o2dlm_eviction_cb(int node_num, void *data)
{
	struct ocfs2_cluster_connection *conn = data;

	mlog(ML_NOTICE, "o2dlm has evicted node %d from group %.*s\n",
	     node_num, conn->cc_namelen, conn->cc_name);

	conn->cc_recovery_handler(node_num, conn->cc_recovery_data);
}