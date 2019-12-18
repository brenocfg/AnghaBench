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
struct macvtap_queue {int /*<<< orphan*/  sk; int /*<<< orphan*/  vlan; } ;
struct macvlan_dev {int /*<<< orphan*/  tap; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct macvlan_dev* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void macvtap_put_queue(struct macvtap_queue *q)
{
	struct macvlan_dev *vlan;

	rtnl_lock();
	vlan = rtnl_dereference(q->vlan);
	if (vlan) {
		rcu_assign_pointer(vlan->tap, NULL);
		rcu_assign_pointer(q->vlan, NULL);
		sock_put(&q->sk);
	}

	rtnl_unlock();

	synchronize_rcu();
	sock_put(&q->sk);
}