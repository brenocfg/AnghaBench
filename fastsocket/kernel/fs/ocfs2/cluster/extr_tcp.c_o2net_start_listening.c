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
struct o2nm_node {int /*<<< orphan*/  nd_num; int /*<<< orphan*/  nd_ipv4_port; int /*<<< orphan*/  nd_ipv4_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_KTHREAD ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * o2net_listen_sock ; 
 int o2net_open_listening_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * o2net_wq ; 
 int /*<<< orphan*/  o2quo_conn_up (int /*<<< orphan*/ ) ; 

int o2net_start_listening(struct o2nm_node *node)
{
	int ret = 0;

	BUG_ON(o2net_wq != NULL);
	BUG_ON(o2net_listen_sock != NULL);

	mlog(ML_KTHREAD, "starting o2net thread...\n");
	o2net_wq = create_singlethread_workqueue("o2net");
	if (o2net_wq == NULL) {
		mlog(ML_ERROR, "unable to launch o2net thread\n");
		return -ENOMEM; /* ? */
	}

	ret = o2net_open_listening_sock(node->nd_ipv4_address,
					node->nd_ipv4_port);
	if (ret) {
		destroy_workqueue(o2net_wq);
		o2net_wq = NULL;
	} else
		o2quo_conn_up(node->nd_num);

	return ret;
}