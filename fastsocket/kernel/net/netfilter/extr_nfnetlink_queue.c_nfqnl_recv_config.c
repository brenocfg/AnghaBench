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
typedef  int /*<<< orphan*/  u_int16_t ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfqnl_msg_config_params {int /*<<< orphan*/  copy_range; int /*<<< orphan*/  copy_mode; } ;
struct nfqnl_msg_config_cmd {int command; int /*<<< orphan*/  pf; } ;
struct nfqnl_instance {scalar_t__ peer_pid; int flags; int /*<<< orphan*/  lock; void* queue_maxlen; } ;
struct nfgenmsg {int /*<<< orphan*/  res_id; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_ERR (struct nfqnl_instance*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 size_t NFQA_CFG_CMD ; 
 size_t NFQA_CFG_FLAGS ; 
 int NFQA_CFG_F_MAX ; 
 size_t NFQA_CFG_MASK ; 
 size_t NFQA_CFG_PARAMS ; 
 size_t NFQA_CFG_QUEUE_MAXLEN ; 
#define  NFQNL_CFG_CMD_BIND 131 
#define  NFQNL_CFG_CMD_PF_BIND 130 
#define  NFQNL_CFG_CMD_PF_UNBIND 129 
#define  NFQNL_CFG_CMD_UNBIND 128 
 struct nfgenmsg* NLMSG_DATA (struct nlmsghdr const*) ; 
 int PTR_ERR (struct nfqnl_instance*) ; 
 struct nfqnl_instance* instance_create (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  instance_destroy (struct nfqnl_instance*) ; 
 struct nfqnl_instance* instance_lookup (int /*<<< orphan*/ ) ; 
 int nf_register_queue_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nf_unregister_queue_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfqh ; 
 int /*<<< orphan*/  nfqnl_set_mode (struct nfqnl_instance*,int /*<<< orphan*/ ,void*) ; 
 void* nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfqnl_recv_config(struct sock *ctnl, struct sk_buff *skb,
		  const struct nlmsghdr *nlh,
		  const struct nlattr * const nfqa[])
{
	struct nfgenmsg *nfmsg = NLMSG_DATA(nlh);
	u_int16_t queue_num = ntohs(nfmsg->res_id);
	struct nfqnl_instance *queue;
	struct nfqnl_msg_config_cmd *cmd = NULL;
	int ret = 0;

	if (nfqa[NFQA_CFG_CMD]) {
		cmd = nla_data(nfqa[NFQA_CFG_CMD]);

		/* Commands without queue context - might sleep */
		switch (cmd->command) {
		case NFQNL_CFG_CMD_PF_BIND:
			return nf_register_queue_handler(ntohs(cmd->pf),
							 &nfqh);
		case NFQNL_CFG_CMD_PF_UNBIND:
			return nf_unregister_queue_handler(ntohs(cmd->pf),
							   &nfqh);
		}
	}

	rcu_read_lock();
	queue = instance_lookup(queue_num);
	if (queue && queue->peer_pid != NETLINK_CB(skb).pid) {
		ret = -EPERM;
		goto err_out_unlock;
	}

	if (cmd != NULL) {
		switch (cmd->command) {
		case NFQNL_CFG_CMD_BIND:
			if (queue) {
				ret = -EBUSY;
				goto err_out_unlock;
			}
			queue = instance_create(queue_num, NETLINK_CB(skb).pid);
			if (IS_ERR(queue)) {
				ret = PTR_ERR(queue);
				goto err_out_unlock;
			}
			break;
		case NFQNL_CFG_CMD_UNBIND:
			if (!queue) {
				ret = -ENODEV;
				goto err_out_unlock;
			}
			instance_destroy(queue);
			break;
		case NFQNL_CFG_CMD_PF_BIND:
		case NFQNL_CFG_CMD_PF_UNBIND:
			break;
		default:
			ret = -ENOTSUPP;
			break;
		}
	}

	if (nfqa[NFQA_CFG_PARAMS]) {
		struct nfqnl_msg_config_params *params;

		if (!queue) {
			ret = -ENODEV;
			goto err_out_unlock;
		}
		params = nla_data(nfqa[NFQA_CFG_PARAMS]);
		nfqnl_set_mode(queue, params->copy_mode,
				ntohl(params->copy_range));
	}

	if (nfqa[NFQA_CFG_QUEUE_MAXLEN]) {
		__be32 *queue_maxlen;

		if (!queue) {
			ret = -ENODEV;
			goto err_out_unlock;
		}
		queue_maxlen = nla_data(nfqa[NFQA_CFG_QUEUE_MAXLEN]);
		spin_lock_bh(&queue->lock);
		queue->queue_maxlen = ntohl(*queue_maxlen);
		spin_unlock_bh(&queue->lock);
	}

	if (nfqa[NFQA_CFG_FLAGS]) {
		__u32 flags, mask;

		if (!queue) {
			ret = -ENODEV;
			goto err_out_unlock;
		}

		if (!nfqa[NFQA_CFG_MASK]) {
			/* A mask is needed to specify which flags are being
			 * changed.
			 */
			ret = -EINVAL;
			goto err_out_unlock;
		}

		flags = ntohl(nla_get_be32(nfqa[NFQA_CFG_FLAGS]));
		mask = ntohl(nla_get_be32(nfqa[NFQA_CFG_MASK]));

		if (flags >= NFQA_CFG_F_MAX) {
			ret = -EOPNOTSUPP;
			goto err_out_unlock;
		}

		spin_lock_bh(&queue->lock);
		queue->flags &= ~mask;
		queue->flags |= flags & mask;
		spin_unlock_bh(&queue->lock);
	}

err_out_unlock:
	rcu_read_unlock();
	return ret;
}