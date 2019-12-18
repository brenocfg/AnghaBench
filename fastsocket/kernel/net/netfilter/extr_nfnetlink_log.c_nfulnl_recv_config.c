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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfulnl_msg_config_mode {int /*<<< orphan*/  copy_range; int /*<<< orphan*/  copy_mode; } ;
struct nfulnl_msg_config_cmd {int command; } ;
struct nfulnl_instance {scalar_t__ peer_pid; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; int /*<<< orphan*/  res_id; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_ERR (struct nfulnl_instance*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 size_t NFULA_CFG_CMD ; 
 size_t NFULA_CFG_FLAGS ; 
 size_t NFULA_CFG_MODE ; 
 size_t NFULA_CFG_NLBUFSIZ ; 
 size_t NFULA_CFG_QTHRESH ; 
 size_t NFULA_CFG_TIMEOUT ; 
#define  NFULNL_CFG_CMD_BIND 131 
#define  NFULNL_CFG_CMD_PF_BIND 130 
#define  NFULNL_CFG_CMD_PF_UNBIND 129 
#define  NFULNL_CFG_CMD_UNBIND 128 
 struct nfgenmsg* NLMSG_DATA (struct nlmsghdr const*) ; 
 int PTR_ERR (struct nfulnl_instance*) ; 
 struct nfulnl_instance* instance_create (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  instance_destroy (struct nfulnl_instance*) ; 
 struct nfulnl_instance* instance_lookup_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instance_put (struct nfulnl_instance*) ; 
 int nf_log_bind_pf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_log_unbind_pf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_logger ; 
 int /*<<< orphan*/  nfulnl_set_flags (struct nfulnl_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_set_mode (struct nfulnl_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_set_nlbufsiz (struct nfulnl_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_set_qthresh (struct nfulnl_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_set_timeout (struct nfulnl_instance*,int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfulnl_recv_config(struct sock *ctnl, struct sk_buff *skb,
		   const struct nlmsghdr *nlh,
		   const struct nlattr * const nfula[])
{
	struct nfgenmsg *nfmsg = NLMSG_DATA(nlh);
	u_int16_t group_num = ntohs(nfmsg->res_id);
	struct nfulnl_instance *inst;
	struct nfulnl_msg_config_cmd *cmd = NULL;
	int ret = 0;

	if (nfula[NFULA_CFG_CMD]) {
		u_int8_t pf = nfmsg->nfgen_family;
		cmd = nla_data(nfula[NFULA_CFG_CMD]);

		/* Commands without queue context */
		switch (cmd->command) {
		case NFULNL_CFG_CMD_PF_BIND:
			return nf_log_bind_pf(pf, &nfulnl_logger);
		case NFULNL_CFG_CMD_PF_UNBIND:
			nf_log_unbind_pf(pf);
			return 0;
		}
	}

	inst = instance_lookup_get(group_num);
	if (inst && inst->peer_pid != NETLINK_CB(skb).pid) {
		ret = -EPERM;
		goto out_put;
	}

	if (cmd != NULL) {
		switch (cmd->command) {
		case NFULNL_CFG_CMD_BIND:
			if (inst) {
				ret = -EBUSY;
				goto out_put;
			}

			inst = instance_create(group_num,
					       NETLINK_CB(skb).pid);
			if (IS_ERR(inst)) {
				ret = PTR_ERR(inst);
				goto out;
			}
			break;
		case NFULNL_CFG_CMD_UNBIND:
			if (!inst) {
				ret = -ENODEV;
				goto out;
			}

			instance_destroy(inst);
			goto out;
		default:
			ret = -ENOTSUPP;
			break;
		}
	}

	if (nfula[NFULA_CFG_MODE]) {
		struct nfulnl_msg_config_mode *params;
		params = nla_data(nfula[NFULA_CFG_MODE]);

		if (!inst) {
			ret = -ENODEV;
			goto out;
		}
		nfulnl_set_mode(inst, params->copy_mode,
				ntohl(params->copy_range));
	}

	if (nfula[NFULA_CFG_TIMEOUT]) {
		__be32 timeout = nla_get_be32(nfula[NFULA_CFG_TIMEOUT]);

		if (!inst) {
			ret = -ENODEV;
			goto out;
		}
		nfulnl_set_timeout(inst, ntohl(timeout));
	}

	if (nfula[NFULA_CFG_NLBUFSIZ]) {
		__be32 nlbufsiz = nla_get_be32(nfula[NFULA_CFG_NLBUFSIZ]);

		if (!inst) {
			ret = -ENODEV;
			goto out;
		}
		nfulnl_set_nlbufsiz(inst, ntohl(nlbufsiz));
	}

	if (nfula[NFULA_CFG_QTHRESH]) {
		__be32 qthresh = nla_get_be32(nfula[NFULA_CFG_QTHRESH]);

		if (!inst) {
			ret = -ENODEV;
			goto out;
		}
		nfulnl_set_qthresh(inst, ntohl(qthresh));
	}

	if (nfula[NFULA_CFG_FLAGS]) {
		__be16 flags = nla_get_be16(nfula[NFULA_CFG_FLAGS]);

		if (!inst) {
			ret = -ENODEV;
			goto out;
		}
		nfulnl_set_flags(inst, ntohs(flags));
	}

out_put:
	instance_put(inst);
out:
	return ret;
}