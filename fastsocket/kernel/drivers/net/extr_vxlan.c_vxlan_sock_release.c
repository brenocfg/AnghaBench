#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vxlan_sock {int /*<<< orphan*/  del_work; int /*<<< orphan*/  hlist; int /*<<< orphan*/  refcnt; TYPE_1__* sock; } ;
struct vxlan_net {int /*<<< orphan*/  sock_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 struct vxlan_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_net_id ; 
 int /*<<< orphan*/  vxlan_wq ; 

void vxlan_sock_release(struct vxlan_sock *vs)
{
	struct vxlan_net *vn = net_generic(sock_net(vs->sock->sk), vxlan_net_id);

	if (!atomic_dec_and_test(&vs->refcnt))
		return;

	spin_lock(&vn->sock_lock);
	hlist_del_rcu(&vs->hlist);
	spin_unlock(&vn->sock_lock);

	queue_work(vxlan_wq, &vs->del_work);
}