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
struct xt_target_param {scalar_t__ hooknum; int /*<<< orphan*/ * out; struct nf_nat_multi_range_compat* targinfo; } ;
struct sk_buff {int dummy; } ;
struct nf_nat_multi_range_compat {int /*<<< orphan*/ * range; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int IP_CT_IS_REPLY ; 
 int IP_CT_NEW ; 
 int IP_CT_RELATED ; 
 int /*<<< orphan*/  IP_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int) ; 
 scalar_t__ NF_INET_POST_ROUTING ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 unsigned int nf_nat_setup_info (struct nf_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ipt_snat_target(struct sk_buff *skb, const struct xt_target_param *par)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	const struct nf_nat_multi_range_compat *mr = par->targinfo;

	NF_CT_ASSERT(par->hooknum == NF_INET_POST_ROUTING);

	ct = nf_ct_get(skb, &ctinfo);

	/* Connection must be valid and new. */
	NF_CT_ASSERT(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
			    ctinfo == IP_CT_RELATED + IP_CT_IS_REPLY));
	NF_CT_ASSERT(par->out != NULL);

	return nf_nat_setup_info(ct, &mr->range[0], IP_NAT_MANIP_SRC);
}