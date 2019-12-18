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
typedef  int /*<<< orphan*/  u32 ;
struct vxlan_sock {int dummy; } ;
struct vxlan_dev {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct vxlan_sock* vxlan_find_sock (struct net*,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* vxlan_vs_find_vni (struct vxlan_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vxlan_dev *vxlan_find_vni(struct net *net, u32 id, __be16 port)
{
	struct vxlan_sock *vs;

	vs = vxlan_find_sock(net, port);
	if (!vs)
		return NULL;

	return vxlan_vs_find_vni(vs, id);
}