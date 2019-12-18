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
typedef  int /*<<< orphan*/  vxlan_rcv_t ;
struct vxlan_sock {int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * rcv; } ;
struct vxlan_net {int /*<<< orphan*/  sock_lock; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct vxlan_sock* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct vxlan_sock*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct vxlan_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vxlan_sock* vxlan_find_sock (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_net_id ; 
 struct vxlan_sock* vxlan_socket_create (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

struct vxlan_sock *vxlan_sock_add(struct net *net, __be16 port,
				  vxlan_rcv_t *rcv, void *data,
				  bool no_share)
{
	struct vxlan_net *vn = net_generic(net, vxlan_net_id);
	struct vxlan_sock *vs;

	vs = vxlan_socket_create(net, port, rcv, data);
	if (!IS_ERR(vs))
		return vs;

	if (no_share)	/* Return error if sharing is not allowed. */
		return vs;

	spin_lock(&vn->sock_lock);
	vs = vxlan_find_sock(net, port);
	if (vs) {
		if (vs->rcv == rcv)
			atomic_inc(&vs->refcnt);
		else
			vs = ERR_PTR(-EBUSY);
	}
	spin_unlock(&vn->sock_lock);

	if (!vs)
		vs = ERR_PTR(-EINVAL);

	return vs;
}