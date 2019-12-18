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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  remote_vni; } ;
struct vxlan_dev {TYPE_1__ default_dst; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dev; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 size_t NDA_DST ; 
 size_t NDA_IFINDEX ; 
 size_t NDA_PORT ; 
 size_t NDA_VNI ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static int vxlan_fdb_parse(struct nlattr *tb[], struct vxlan_dev *vxlan,
			   __be32 *ip, __be16 *port, u32 *vni, u32 *ifindex)
{
	struct net *net = dev_net(vxlan->dev);

	if (tb[NDA_DST]) {
		if (nla_len(tb[NDA_DST]) != sizeof(__be32))
			return -EAFNOSUPPORT;

		*ip = nla_get_be32(tb[NDA_DST]);
	} else {
		*ip = htonl(INADDR_ANY);
	}

	if (tb[NDA_PORT]) {
		if (nla_len(tb[NDA_PORT]) != sizeof(__be16))
			return -EINVAL;
		*port = nla_get_be16(tb[NDA_PORT]);
	} else {
		*port = vxlan->dst_port;
	}

	if (tb[NDA_VNI]) {
		if (nla_len(tb[NDA_VNI]) != sizeof(u32))
			return -EINVAL;
		*vni = nla_get_u32(tb[NDA_VNI]);
	} else {
		*vni = vxlan->default_dst.remote_vni;
	}

	if (tb[NDA_IFINDEX]) {
		struct net_device *tdev;

		if (nla_len(tb[NDA_IFINDEX]) != sizeof(u32))
			return -EINVAL;
		*ifindex = nla_get_u32(tb[NDA_IFINDEX]);
		tdev = dev_get_by_index(net, *ifindex);
		if (!tdev)
			return -EADDRNOTAVAIL;
		dev_put(tdev);
	} else {
		*ifindex = 0;
	}

	return 0;
}