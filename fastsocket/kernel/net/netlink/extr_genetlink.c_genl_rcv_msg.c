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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; int /*<<< orphan*/  nlmsg_type; } ;
struct netlink_dump_control {int /*<<< orphan*/  done; int /*<<< orphan*/ * dump; } ;
struct net {int /*<<< orphan*/  genl_sock; } ;
struct genlmsghdr {int /*<<< orphan*/  cmd; } ;
struct genl_ops {int flags; int (* doit ) (struct sk_buff*,struct genl_info*) ;int /*<<< orphan*/  policy; int /*<<< orphan*/  done; int /*<<< orphan*/ * dumpit; } ;
struct genl_info {scalar_t__ attrs; void* userhdr; void* genlhdr; struct nlmsghdr* nlhdr; int /*<<< orphan*/  snd_pid; int /*<<< orphan*/  snd_seq; } ;
struct genl_family {int hdrsize; scalar_t__ attrbuf; int /*<<< orphan*/  maxattr; int /*<<< orphan*/  netnsok; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int GENL_ADMIN_PERM ; 
 int GENL_HDRLEN ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_DUMP ; 
 struct genl_family* genl_family_find_byid (int /*<<< orphan*/ ) ; 
 struct genl_ops* genl_get_cmd (int /*<<< orphan*/ ,struct genl_family*) ; 
 int /*<<< orphan*/  genl_info_net_set (struct genl_info*,struct net*) ; 
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int netlink_dump_start (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct netlink_dump_control*) ; 
 void* nlmsg_data (struct nlmsghdr*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 
 int nlmsg_parse (struct nlmsghdr*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ security_netlink_recv (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,struct genl_info*) ; 

__attribute__((used)) static int genl_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	struct genl_ops *ops;
	struct genl_family *family;
	struct net *net = sock_net(skb->sk);
	struct genl_info info;
	struct genlmsghdr *hdr = nlmsg_data(nlh);
	int hdrlen, err;

	family = genl_family_find_byid(nlh->nlmsg_type);
	if (family == NULL)
		return -ENOENT;

	/* this family doesn't exist in this netns */
	if (!family->netnsok && !net_eq(net, &init_net))
		return -ENOENT;

	hdrlen = GENL_HDRLEN + family->hdrsize;
	if (nlh->nlmsg_len < nlmsg_msg_size(hdrlen))
		return -EINVAL;

	ops = genl_get_cmd(hdr->cmd, family);
	if (ops == NULL)
		return -EOPNOTSUPP;

	if ((ops->flags & GENL_ADMIN_PERM) &&
	    security_netlink_recv(skb, CAP_NET_ADMIN))
		return -EPERM;

	if (nlh->nlmsg_flags & NLM_F_DUMP) {
		if (ops->dumpit == NULL)
			return -EOPNOTSUPP;

		genl_unlock();
		{
			struct netlink_dump_control c = {
				.dump = ops->dumpit,
				.done = ops->done,
			};
			err = netlink_dump_start(net->genl_sock, skb, nlh, &c);
		}
		genl_lock();
		return err;
	}

	if (ops->doit == NULL)
		return -EOPNOTSUPP;

	if (family->attrbuf) {
		err = nlmsg_parse(nlh, hdrlen, family->attrbuf, family->maxattr,
				  ops->policy);
		if (err < 0)
			return err;
	}

	info.snd_seq = nlh->nlmsg_seq;
	info.snd_pid = NETLINK_CB(skb).pid;
	info.nlhdr = nlh;
	info.genlhdr = nlmsg_data(nlh);
	info.userhdr = nlmsg_data(nlh) + GENL_HDRLEN;
	info.attrs = family->attrbuf;
	genl_info_net_set(&info, net);

	return ops->doit(skb, &info);
}