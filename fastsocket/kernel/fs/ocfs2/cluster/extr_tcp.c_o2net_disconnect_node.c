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
struct o2nm_node {int /*<<< orphan*/  nd_num; } ;
struct o2net_node {int /*<<< orphan*/  nn_still_up; int /*<<< orphan*/  nn_connect_work; int /*<<< orphan*/  nn_connect_expired; int /*<<< orphan*/  nn_lock; int /*<<< orphan*/  nn_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 struct o2net_node* o2net_nn_from_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_set_nn_state (struct o2net_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ o2net_wq ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void o2net_disconnect_node(struct o2nm_node *node)
{
	struct o2net_node *nn = o2net_nn_from_num(node->nd_num);

	/* don't reconnect until it's heartbeating again */
	spin_lock(&nn->nn_lock);
	atomic_set(&nn->nn_timeout, 0);
	o2net_set_nn_state(nn, NULL, 0, -ENOTCONN);
	spin_unlock(&nn->nn_lock);

	if (o2net_wq) {
		cancel_delayed_work(&nn->nn_connect_expired);
		cancel_delayed_work(&nn->nn_connect_work);
		cancel_delayed_work(&nn->nn_still_up);
		flush_workqueue(o2net_wq);
	}
}