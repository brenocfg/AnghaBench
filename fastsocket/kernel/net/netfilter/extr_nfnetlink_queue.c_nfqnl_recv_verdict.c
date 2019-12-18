#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfqnl_msg_verdict_hdr {int /*<<< orphan*/  id; int /*<<< orphan*/  verdict; } ;
struct nfqnl_instance {scalar_t__ peer_pid; } ;
struct nfgenmsg {int /*<<< orphan*/  res_id; } ;
struct nf_queue_entry {TYPE_1__* skb; } ;
struct TYPE_4__ {scalar_t__ pid; } ;
struct TYPE_3__ {void* mark; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int EPERM ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 size_t NFQA_MARK ; 
 size_t NFQA_PAYLOAD ; 
 size_t NFQA_VERDICT_HDR ; 
 unsigned int NF_DROP ; 
 unsigned int NF_MAX_VERDICT ; 
 unsigned int NF_VERDICT_MASK ; 
 struct nfgenmsg* NLMSG_DATA (struct nlmsghdr const*) ; 
 struct nf_queue_entry* find_dequeue_entry (struct nfqnl_instance*,void*) ; 
 struct nfqnl_instance* instance_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_reinject (struct nf_queue_entry*,unsigned int) ; 
 scalar_t__ nfqnl_mangle (struct nfqnl_msg_verdict_hdr*,int /*<<< orphan*/ ,struct nf_queue_entry*) ; 
 struct nfqnl_msg_verdict_hdr* nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_len (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int
nfqnl_recv_verdict(struct sock *ctnl, struct sk_buff *skb,
		   const struct nlmsghdr *nlh,
		   const struct nlattr * const nfqa[])
{
	struct nfgenmsg *nfmsg = NLMSG_DATA(nlh);
	u_int16_t queue_num = ntohs(nfmsg->res_id);

	struct nfqnl_msg_verdict_hdr *vhdr;
	struct nfqnl_instance *queue;
	unsigned int verdict;
	struct nf_queue_entry *entry;
	int err;

	rcu_read_lock();
	queue = instance_lookup(queue_num);
	if (!queue) {
		err = -ENODEV;
		goto err_out_unlock;
	}

	if (queue->peer_pid != NETLINK_CB(skb).pid) {
		err = -EPERM;
		goto err_out_unlock;
	}

	if (!nfqa[NFQA_VERDICT_HDR]) {
		err = -EINVAL;
		goto err_out_unlock;
	}

	vhdr = nla_data(nfqa[NFQA_VERDICT_HDR]);
	verdict = ntohl(vhdr->verdict);

	if ((verdict & NF_VERDICT_MASK) > NF_MAX_VERDICT) {
		err = -EINVAL;
		goto err_out_unlock;
	}

	entry = find_dequeue_entry(queue, ntohl(vhdr->id));
	if (entry == NULL) {
		err = -ENOENT;
		goto err_out_unlock;
	}
	rcu_read_unlock();

	if (nfqa[NFQA_PAYLOAD]) {
		if (nfqnl_mangle(nla_data(nfqa[NFQA_PAYLOAD]),
				 nla_len(nfqa[NFQA_PAYLOAD]), entry) < 0)
			verdict = NF_DROP;
	}

	if (nfqa[NFQA_MARK])
		entry->skb->mark = ntohl(nla_get_be32(nfqa[NFQA_MARK]));

	nf_reinject(entry, verdict);
	return 0;

err_out_unlock:
	rcu_read_unlock();
	return err;
}