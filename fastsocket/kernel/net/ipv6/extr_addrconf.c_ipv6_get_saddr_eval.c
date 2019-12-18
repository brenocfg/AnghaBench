#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct ipv6_saddr_score {int rule; int scopedist; int matchlen; int /*<<< orphan*/  scorebits; TYPE_4__* ifa; int /*<<< orphan*/  addr_type; } ;
struct ipv6_saddr_dst {int scope; int prefs; int /*<<< orphan*/ * addr; int /*<<< orphan*/  label; int /*<<< orphan*/  ifindex; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  addr; TYPE_3__* idev; } ;
struct TYPE_6__ {int use_tempaddr; } ;
struct TYPE_7__ {TYPE_2__ cnf; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int IFA_F_DEPRECATED ; 
 int IFA_F_HOMEADDRESS ; 
 int IFA_F_OPTIMISTIC ; 
 int IFA_F_TEMPORARY ; 
 int IPV6_PREFER_SRC_COA ; 
 int IPV6_PREFER_SRC_PUBLIC ; 
 int IPV6_PREFER_SRC_TMP ; 
#define  IPV6_SADDR_RULE_HOA 137 
#define  IPV6_SADDR_RULE_INIT 136 
#define  IPV6_SADDR_RULE_LABEL 135 
#define  IPV6_SADDR_RULE_LOCAL 134 
#define  IPV6_SADDR_RULE_OIF 133 
#define  IPV6_SADDR_RULE_ORCHID 132 
#define  IPV6_SADDR_RULE_PREFERRED 131 
#define  IPV6_SADDR_RULE_PREFIX 130 
#define  IPV6_SADDR_RULE_PRIVACY 129 
#define  IPV6_SADDR_RULE_SCOPE 128 
 int __ipv6_addr_src_scope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int ipv6_addr_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_label (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipv6_addr_orchid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_saddr_preferred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipv6_get_saddr_eval(struct net *net,
			       struct ipv6_saddr_score *score,
			       struct ipv6_saddr_dst *dst,
			       int i)
{
	int ret;

	if (i <= score->rule) {
		switch (i) {
		case IPV6_SADDR_RULE_SCOPE:
			ret = score->scopedist;
			break;
		case IPV6_SADDR_RULE_PREFIX:
			ret = score->matchlen;
			break;
		default:
			ret = !!test_bit(i, score->scorebits);
		}
		goto out;
	}

	switch (i) {
	case IPV6_SADDR_RULE_INIT:
		/* Rule 0: remember if hiscore is not ready yet */
		ret = !!score->ifa;
		break;
	case IPV6_SADDR_RULE_LOCAL:
		/* Rule 1: Prefer same address */
		ret = ipv6_addr_equal(&score->ifa->addr, dst->addr);
		break;
	case IPV6_SADDR_RULE_SCOPE:
		/* Rule 2: Prefer appropriate scope
		 *
		 *      ret
		 *       ^
		 *    -1 |  d 15
		 *    ---+--+-+---> scope
		 *       |
		 *       |             d is scope of the destination.
		 *  B-d  |  \
		 *       |   \      <- smaller scope is better if
		 *  B-15 |    \        if scope is enough for destinaion.
		 *       |             ret = B - scope (-1 <= scope >= d <= 15).
		 * d-C-1 | /
		 *       |/         <- greater is better
		 *   -C  /             if scope is not enough for destination.
		 *      /|             ret = scope - C (-1 <= d < scope <= 15).
		 *
		 * d - C - 1 < B -15 (for all -1 <= d <= 15).
		 * C > d + 14 - B >= 15 + 14 - B = 29 - B.
		 * Assume B = 0 and we get C > 29.
		 */
		ret = __ipv6_addr_src_scope(score->addr_type);
		if (ret >= dst->scope)
			ret = -ret;
		else
			ret -= 128;	/* 30 is enough */
		score->scopedist = ret;
		break;
	case IPV6_SADDR_RULE_PREFERRED:
		/* Rule 3: Avoid deprecated and optimistic addresses */
		ret = ipv6_saddr_preferred(score->addr_type) ||
		      !(score->ifa->flags & (IFA_F_DEPRECATED|IFA_F_OPTIMISTIC));
		break;
#ifdef CONFIG_IPV6_MIP6
	case IPV6_SADDR_RULE_HOA:
	    {
		/* Rule 4: Prefer home address */
		int prefhome = !(dst->prefs & IPV6_PREFER_SRC_COA);
		ret = !(score->ifa->flags & IFA_F_HOMEADDRESS) ^ prefhome;
		break;
	    }
#endif
	case IPV6_SADDR_RULE_OIF:
		/* Rule 5: Prefer outgoing interface */
		ret = (!dst->ifindex ||
		       dst->ifindex == score->ifa->idev->dev->ifindex);
		break;
	case IPV6_SADDR_RULE_LABEL:
		/* Rule 6: Prefer matching label */
		ret = ipv6_addr_label(net,
				      &score->ifa->addr, score->addr_type,
				      score->ifa->idev->dev->ifindex) == dst->label;
		break;
#ifdef CONFIG_IPV6_PRIVACY
	case IPV6_SADDR_RULE_PRIVACY:
	    {
		/* Rule 7: Prefer public address
		 * Note: prefer temprary address if use_tempaddr >= 2
		 */
		int preftmp = dst->prefs & (IPV6_PREFER_SRC_PUBLIC|IPV6_PREFER_SRC_TMP) ?
				!!(dst->prefs & IPV6_PREFER_SRC_TMP) :
				score->ifa->idev->cnf.use_tempaddr >= 2;
		ret = (!(score->ifa->flags & IFA_F_TEMPORARY)) ^ preftmp;
		break;
	    }
#endif
	case IPV6_SADDR_RULE_ORCHID:
		/* Rule 8-: Prefer ORCHID vs ORCHID or
		 *	    non-ORCHID vs non-ORCHID
		 */
		ret = !(ipv6_addr_orchid(&score->ifa->addr) ^
			ipv6_addr_orchid(dst->addr));
		break;
	case IPV6_SADDR_RULE_PREFIX:
		/* Rule 8: Use longest matching prefix */
		score->matchlen = ret = ipv6_addr_diff(&score->ifa->addr,
						       dst->addr);
		break;
	default:
		ret = 0;
	}

	if (ret)
		__set_bit(i, score->scorebits);
	score->rule = i;
out:
	return ret;
}