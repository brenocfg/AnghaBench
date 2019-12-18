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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nfgenmsg {scalar_t__ res_id; int /*<<< orphan*/  version; int /*<<< orphan*/  nfgen_family; } ;
typedef  enum ipset_cmd { ____Placeholder_ipset_cmd } ipset_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int NFNL_SUBSYS_IPSET ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 

__attribute__((used)) static struct nlmsghdr *
start_msg(struct sk_buff *skb, u32 pid, u32 seq, unsigned int flags,
	  enum ipset_cmd cmd)
{
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfmsg;

	nlh = nlmsg_put(skb, pid, seq, cmd | (NFNL_SUBSYS_IPSET << 8),
			sizeof(*nfmsg), flags);
	if (nlh == NULL)
		return NULL;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family = AF_INET;
	nfmsg->version = NFNETLINK_V0;
	nfmsg->res_id = 0;

	return nlh;
}