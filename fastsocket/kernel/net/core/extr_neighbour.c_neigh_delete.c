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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct neighbour {int dummy; } ;
struct neigh_table {scalar_t__ family; scalar_t__ key_len; struct neigh_table* next; } ;
struct ndmsg {scalar_t__ ndm_family; int ndm_flags; scalar_t__ ndm_ifindex; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  NDA_DST ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int NTF_PROXY ; 
 int /*<<< orphan*/  NUD_FAILED ; 
 struct net_device* dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct neighbour* neigh_lookup (struct neigh_table*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct neigh_table* neigh_tables ; 
 int /*<<< orphan*/  neigh_tbl_lock ; 
 int neigh_update (struct neighbour*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct nlattr* nlmsg_find_attr (struct nlmsghdr*,int,int /*<<< orphan*/ ) ; 
 int nlmsg_len (struct nlmsghdr*) ; 
 int pneigh_delete (struct neigh_table*,struct net*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neigh_delete(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct ndmsg *ndm;
	struct nlattr *dst_attr;
	struct neigh_table *tbl;
	struct net_device *dev = NULL;
	int err = -EINVAL;

	if (nlmsg_len(nlh) < sizeof(*ndm))
		goto out;

	dst_attr = nlmsg_find_attr(nlh, sizeof(*ndm), NDA_DST);
	if (dst_attr == NULL)
		goto out;

	ndm = nlmsg_data(nlh);
	if (ndm->ndm_ifindex) {
		dev = dev_get_by_index(net, ndm->ndm_ifindex);
		if (dev == NULL) {
			err = -ENODEV;
			goto out;
		}
	}

	read_lock(&neigh_tbl_lock);
	for (tbl = neigh_tables; tbl; tbl = tbl->next) {
		struct neighbour *neigh;

		if (tbl->family != ndm->ndm_family)
			continue;
		read_unlock(&neigh_tbl_lock);

		if (nla_len(dst_attr) < tbl->key_len)
			goto out_dev_put;

		if (ndm->ndm_flags & NTF_PROXY) {
			err = pneigh_delete(tbl, net, nla_data(dst_attr), dev);
			goto out_dev_put;
		}

		if (dev == NULL)
			goto out_dev_put;

		neigh = neigh_lookup(tbl, nla_data(dst_attr), dev);
		if (neigh == NULL) {
			err = -ENOENT;
			goto out_dev_put;
		}

		err = neigh_update(neigh, NULL, NUD_FAILED,
				   NEIGH_UPDATE_F_OVERRIDE |
				   NEIGH_UPDATE_F_ADMIN);
		neigh_release(neigh);
		goto out_dev_put;
	}
	read_unlock(&neigh_tbl_lock);
	err = -EAFNOSUPPORT;

out_dev_put:
	if (dev)
		dev_put(dev);
out:
	return err;
}