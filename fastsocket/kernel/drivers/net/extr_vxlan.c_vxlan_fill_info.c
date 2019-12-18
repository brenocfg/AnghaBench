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
struct vxlan_rdst {scalar_t__ remote_ifindex; scalar_t__ remote_ip; scalar_t__ remote_vni; } ;
struct vxlan_dev {int ttl; int tos; int flags; int /*<<< orphan*/  dst_port; scalar_t__ addrmax; scalar_t__ age_interval; scalar_t__ saddr; int /*<<< orphan*/  port_max; int /*<<< orphan*/  port_min; struct vxlan_rdst default_dst; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ifla_vxlan_port_range {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  int /*<<< orphan*/  ports ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_VXLAN_AGEING ; 
 int /*<<< orphan*/  IFLA_VXLAN_GROUP ; 
 int /*<<< orphan*/  IFLA_VXLAN_ID ; 
 int /*<<< orphan*/  IFLA_VXLAN_L2MISS ; 
 int /*<<< orphan*/  IFLA_VXLAN_L3MISS ; 
 int /*<<< orphan*/  IFLA_VXLAN_LEARNING ; 
 int /*<<< orphan*/  IFLA_VXLAN_LIMIT ; 
 int /*<<< orphan*/  IFLA_VXLAN_LINK ; 
 int /*<<< orphan*/  IFLA_VXLAN_LOCAL ; 
 int /*<<< orphan*/  IFLA_VXLAN_PORT ; 
 int /*<<< orphan*/  IFLA_VXLAN_PORT_RANGE ; 
 int /*<<< orphan*/  IFLA_VXLAN_PROXY ; 
 int /*<<< orphan*/  IFLA_VXLAN_RSC ; 
 int /*<<< orphan*/  IFLA_VXLAN_TOS ; 
 int /*<<< orphan*/  IFLA_VXLAN_TTL ; 
 int VXLAN_F_L2MISS ; 
 int VXLAN_F_L3MISS ; 
 int VXLAN_F_LEARN ; 
 int VXLAN_F_PROXY ; 
 int VXLAN_F_RSC ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct ifla_vxlan_port_range*) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vxlan_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	const struct vxlan_dev *vxlan = netdev_priv(dev);
	const struct vxlan_rdst *dst = &vxlan->default_dst;
	struct ifla_vxlan_port_range ports = {
		.low =  htons(vxlan->port_min),
		.high = htons(vxlan->port_max),
	};

	if (nla_put_u32(skb, IFLA_VXLAN_ID, dst->remote_vni))
		goto nla_put_failure;

	if (dst->remote_ip && nla_put_be32(skb, IFLA_VXLAN_GROUP, dst->remote_ip))
		goto nla_put_failure;

	if (dst->remote_ifindex && nla_put_u32(skb, IFLA_VXLAN_LINK, dst->remote_ifindex))
		goto nla_put_failure;

	if (vxlan->saddr && nla_put_be32(skb, IFLA_VXLAN_LOCAL, vxlan->saddr))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_VXLAN_TTL, vxlan->ttl) ||
	    nla_put_u8(skb, IFLA_VXLAN_TOS, vxlan->tos) ||
	    nla_put_u8(skb, IFLA_VXLAN_LEARNING,
			!!(vxlan->flags & VXLAN_F_LEARN)) ||
	    nla_put_u8(skb, IFLA_VXLAN_PROXY,
			!!(vxlan->flags & VXLAN_F_PROXY)) ||
	    nla_put_u8(skb, IFLA_VXLAN_RSC, !!(vxlan->flags & VXLAN_F_RSC)) ||
	    nla_put_u8(skb, IFLA_VXLAN_L2MISS,
			!!(vxlan->flags & VXLAN_F_L2MISS)) ||
	    nla_put_u8(skb, IFLA_VXLAN_L3MISS,
			!!(vxlan->flags & VXLAN_F_L3MISS)) ||
	    nla_put_u32(skb, IFLA_VXLAN_AGEING, vxlan->age_interval) ||
	    nla_put_u32(skb, IFLA_VXLAN_LIMIT, vxlan->addrmax) ||
	    nla_put_be16(skb, IFLA_VXLAN_PORT, vxlan->dst_port))
		goto nla_put_failure;

	if (nla_put(skb, IFLA_VXLAN_PORT_RANGE, sizeof(ports), &ports))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}