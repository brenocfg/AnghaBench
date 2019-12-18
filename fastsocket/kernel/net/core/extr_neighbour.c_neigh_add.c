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
struct pneigh_entry {int flags; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct net_device {scalar_t__ addr_len; } ;
struct net {int dummy; } ;
struct neighbour {int dummy; } ;
struct neigh_table {scalar_t__ family; scalar_t__ key_len; struct neigh_table* next; } ;
struct ndmsg {scalar_t__ ndm_family; int ndm_flags; int /*<<< orphan*/  ndm_state; scalar_t__ ndm_ifindex; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 size_t NDA_DST ; 
 size_t NDA_LLADDR ; 
 int /*<<< orphan*/  NDA_MAX ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 int NTF_PROXY ; 
 int NTF_USE ; 
 int PTR_ERR (struct neighbour*) ; 
 struct neighbour* __neigh_lookup_errno (struct neigh_table*,void*,struct net_device*) ; 
 struct net_device* dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 struct neighbour* neigh_lookup (struct neigh_table*,void*,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct neigh_table* neigh_tables ; 
 int /*<<< orphan*/  neigh_tbl_lock ; 
 int neigh_update (struct neighbour*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pneigh_entry* pneigh_lookup (struct neigh_table*,struct net*,void*,struct net_device*,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neigh_add(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct ndmsg *ndm;
	struct nlattr *tb[NDA_MAX+1];
	struct neigh_table *tbl;
	struct net_device *dev = NULL;
	int err;

	err = nlmsg_parse(nlh, sizeof(*ndm), tb, NDA_MAX, NULL);
	if (err < 0)
		goto out;

	err = -EINVAL;
	if (tb[NDA_DST] == NULL)
		goto out;

	ndm = nlmsg_data(nlh);
	if (ndm->ndm_ifindex) {
		dev = dev_get_by_index(net, ndm->ndm_ifindex);
		if (dev == NULL) {
			err = -ENODEV;
			goto out;
		}

		if (tb[NDA_LLADDR] && nla_len(tb[NDA_LLADDR]) < dev->addr_len)
			goto out_dev_put;
	}

	read_lock(&neigh_tbl_lock);
	for (tbl = neigh_tables; tbl; tbl = tbl->next) {
		int flags = NEIGH_UPDATE_F_ADMIN | NEIGH_UPDATE_F_OVERRIDE;
		struct neighbour *neigh;
		void *dst, *lladdr;

		if (tbl->family != ndm->ndm_family)
			continue;
		read_unlock(&neigh_tbl_lock);

		if (nla_len(tb[NDA_DST]) < tbl->key_len)
			goto out_dev_put;
		dst = nla_data(tb[NDA_DST]);
		lladdr = tb[NDA_LLADDR] ? nla_data(tb[NDA_LLADDR]) : NULL;

		if (ndm->ndm_flags & NTF_PROXY) {
			struct pneigh_entry *pn;

			err = -ENOBUFS;
			pn = pneigh_lookup(tbl, net, dst, dev, 1);
			if (pn) {
				pn->flags = ndm->ndm_flags;
				err = 0;
			}
			goto out_dev_put;
		}

		if (dev == NULL)
			goto out_dev_put;

		neigh = neigh_lookup(tbl, dst, dev);
		if (neigh == NULL) {
			if (!(nlh->nlmsg_flags & NLM_F_CREATE)) {
				err = -ENOENT;
				goto out_dev_put;
			}

			neigh = __neigh_lookup_errno(tbl, dst, dev);
			if (IS_ERR(neigh)) {
				err = PTR_ERR(neigh);
				goto out_dev_put;
			}
		} else {
			if (nlh->nlmsg_flags & NLM_F_EXCL) {
				err = -EEXIST;
				neigh_release(neigh);
				goto out_dev_put;
			}

			if (!(nlh->nlmsg_flags & NLM_F_REPLACE))
				flags &= ~NEIGH_UPDATE_F_OVERRIDE;
		}

		if (ndm->ndm_flags & NTF_USE) {
			neigh_event_send(neigh, NULL);
			err = 0;
		} else
			err = neigh_update(neigh, lladdr, ndm->ndm_state, flags);
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