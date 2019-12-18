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
typedef  int /*<<< orphan*/  u16 ;
typedef  void vxlan_sock ;
struct vxlan_port {void* vs; int /*<<< orphan*/  name; } ;
struct vport_parms {int /*<<< orphan*/  name; struct nlattr* options; int /*<<< orphan*/  dp; } ;
typedef  void vport ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  OVS_TUNNEL_ATTR_DST_PORT ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct nlattr* nla_find_nested (struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct net* ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 void* ovs_vport_alloc (int,int /*<<< orphan*/ *,struct vport_parms const*) ; 
 int /*<<< orphan*/  ovs_vport_free (void*) ; 
 int /*<<< orphan*/  ovs_vxlan_vport_ops ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_rcv ; 
 void* vxlan_sock_add (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 struct vxlan_port* vxlan_vport (void*) ; 

__attribute__((used)) static struct vport *vxlan_tnl_create(const struct vport_parms *parms)
{
	struct net *net = ovs_dp_get_net(parms->dp);
	struct nlattr *options = parms->options;
	struct vxlan_port *vxlan_port;
	struct vxlan_sock *vs;
	struct vport *vport;
	struct nlattr *a;
	u16 dst_port;
	int err;

	if (!options) {
		err = -EINVAL;
		goto error;
	}
	a = nla_find_nested(options, OVS_TUNNEL_ATTR_DST_PORT);
	if (a && nla_len(a) == sizeof(u16)) {
		dst_port = nla_get_u16(a);
	} else {
		/* Require destination port from userspace. */
		err = -EINVAL;
		goto error;
	}

	vport = ovs_vport_alloc(sizeof(struct vxlan_port),
				&ovs_vxlan_vport_ops, parms);
	if (IS_ERR(vport))
		return vport;

	vxlan_port = vxlan_vport(vport);
	strncpy(vxlan_port->name, parms->name, IFNAMSIZ);

	vs = vxlan_sock_add(net, htons(dst_port), vxlan_rcv, vport, true);
	if (IS_ERR(vs)) {
		ovs_vport_free(vport);
		return (void *)vs;
	}
	vxlan_port->vs = vs;

	return vport;

error:
	return ERR_PTR(err);
}