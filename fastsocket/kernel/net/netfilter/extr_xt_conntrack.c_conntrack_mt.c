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
typedef  unsigned int u16 ;
struct xt_match_param {int /*<<< orphan*/  family; struct xt_conntrack_mtinfo2* matchinfo; } ;
struct xt_conntrack_mtinfo2 {int match_flags; int invert_flags; unsigned long expires_min; unsigned long expires_max; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {unsigned long expires; } ;
struct nf_conn {unsigned int status; TYPE_1__ timeout; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 scalar_t__ CTINFO2DIR (int) ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  IPS_DST_NAT_BIT ; 
 int /*<<< orphan*/  IPS_SRC_NAT_BIT ; 
 scalar_t__ IP_CT_DIR_ORIGINAL ; 
 int XT_CONNTRACK_DIRECTION ; 
 int XT_CONNTRACK_EXPIRES ; 
 int XT_CONNTRACK_ORIGDST ; 
 int XT_CONNTRACK_ORIGSRC ; 
 int XT_CONNTRACK_REPLDST ; 
 int XT_CONNTRACK_REPLSRC ; 
 int XT_CONNTRACK_STATE ; 
 unsigned int XT_CONNTRACK_STATE_BIT (int) ; 
 unsigned int XT_CONNTRACK_STATE_DNAT ; 
 unsigned int XT_CONNTRACK_STATE_INVALID ; 
 unsigned int XT_CONNTRACK_STATE_SNAT ; 
 unsigned int XT_CONNTRACK_STATE_UNTRACKED ; 
 int XT_CONNTRACK_STATUS ; 
 int conntrack_mt_origdst (struct nf_conn const*,struct xt_conntrack_mtinfo2 const*,int /*<<< orphan*/ ) ; 
 int conntrack_mt_origsrc (struct nf_conn const*,struct xt_conntrack_mtinfo2 const*,int /*<<< orphan*/ ) ; 
 int conntrack_mt_repldst (struct nf_conn const*,struct xt_conntrack_mtinfo2 const*,int /*<<< orphan*/ ) ; 
 int conntrack_mt_replsrc (struct nf_conn const*,struct xt_conntrack_mtinfo2 const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_proto_port_check (struct xt_conntrack_mtinfo2 const*,struct nf_conn const*) ; 
 unsigned long jiffies ; 
 struct nf_conn const nf_conntrack_untracked ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 

__attribute__((used)) static bool
conntrack_mt(const struct sk_buff *skb, const struct xt_match_param *par,
             u16 state_mask, u16 status_mask)
{
	const struct xt_conntrack_mtinfo2 *info = par->matchinfo;
	enum ip_conntrack_info ctinfo;
	const struct nf_conn *ct;
	unsigned int statebit;

	ct = nf_ct_get(skb, &ctinfo);

	if (ct == &nf_conntrack_untracked)
		statebit = XT_CONNTRACK_STATE_UNTRACKED;
	else if (ct != NULL)
		statebit = XT_CONNTRACK_STATE_BIT(ctinfo);
	else
		statebit = XT_CONNTRACK_STATE_INVALID;

	if (info->match_flags & XT_CONNTRACK_STATE) {
		if (ct != NULL) {
			if (test_bit(IPS_SRC_NAT_BIT, &ct->status))
				statebit |= XT_CONNTRACK_STATE_SNAT;
			if (test_bit(IPS_DST_NAT_BIT, &ct->status))
				statebit |= XT_CONNTRACK_STATE_DNAT;
		}
		if (!!(state_mask & statebit) ^
		    !(info->invert_flags & XT_CONNTRACK_STATE))
			return false;
	}

	if (ct == NULL)
		return info->match_flags & XT_CONNTRACK_STATE;
	if ((info->match_flags & XT_CONNTRACK_DIRECTION) &&
	    (CTINFO2DIR(ctinfo) == IP_CT_DIR_ORIGINAL) ^
	    !!(info->invert_flags & XT_CONNTRACK_DIRECTION))
		return false;

	if (info->match_flags & XT_CONNTRACK_ORIGSRC)
		if (conntrack_mt_origsrc(ct, info, par->family) ^
		    !(info->invert_flags & XT_CONNTRACK_ORIGSRC))
			return false;

	if (info->match_flags & XT_CONNTRACK_ORIGDST)
		if (conntrack_mt_origdst(ct, info, par->family) ^
		    !(info->invert_flags & XT_CONNTRACK_ORIGDST))
			return false;

	if (info->match_flags & XT_CONNTRACK_REPLSRC)
		if (conntrack_mt_replsrc(ct, info, par->family) ^
		    !(info->invert_flags & XT_CONNTRACK_REPLSRC))
			return false;

	if (info->match_flags & XT_CONNTRACK_REPLDST)
		if (conntrack_mt_repldst(ct, info, par->family) ^
		    !(info->invert_flags & XT_CONNTRACK_REPLDST))
			return false;

	if (!ct_proto_port_check(info, ct))
		return false;

	if ((info->match_flags & XT_CONNTRACK_STATUS) &&
	    (!!(status_mask & ct->status) ^
	    !(info->invert_flags & XT_CONNTRACK_STATUS)))
		return false;

	if (info->match_flags & XT_CONNTRACK_EXPIRES) {
		unsigned long expires = 0;

		if (timer_pending(&ct->timeout))
			expires = (ct->timeout.expires - jiffies) / HZ;
		if ((expires >= info->expires_min &&
		    expires <= info->expires_max) ^
		    !(info->invert_flags & XT_CONNTRACK_EXPIRES))
			return false;
	}
	return true;
}