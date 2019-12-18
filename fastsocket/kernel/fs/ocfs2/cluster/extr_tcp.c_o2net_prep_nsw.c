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
struct o2net_status_wait {scalar_t__ ns_status; int /*<<< orphan*/  ns_sys_status; int /*<<< orphan*/  ns_wq; int /*<<< orphan*/  ns_node_item; int /*<<< orphan*/  ns_id; } ;
struct o2net_node {int /*<<< orphan*/  nn_lock; int /*<<< orphan*/  nn_status_list; int /*<<< orphan*/  nn_status_idr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  O2NET_ERR_NONE ; 
 int idr_get_new (int /*<<< orphan*/ *,struct o2net_status_wait*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int o2net_prep_nsw(struct o2net_node *nn, struct o2net_status_wait *nsw)
{
	int ret = 0;

	do {
		if (!idr_pre_get(&nn->nn_status_idr, GFP_ATOMIC)) {
			ret = -EAGAIN;
			break;
		}
		spin_lock(&nn->nn_lock);
		ret = idr_get_new(&nn->nn_status_idr, nsw, &nsw->ns_id);
		if (ret == 0)
			list_add_tail(&nsw->ns_node_item,
				      &nn->nn_status_list);
		spin_unlock(&nn->nn_lock);
	} while (ret == -EAGAIN);

	if (ret == 0)  {
		init_waitqueue_head(&nsw->ns_wq);
		nsw->ns_sys_status = O2NET_ERR_NONE;
		nsw->ns_status = 0;
	}

	return ret;
}