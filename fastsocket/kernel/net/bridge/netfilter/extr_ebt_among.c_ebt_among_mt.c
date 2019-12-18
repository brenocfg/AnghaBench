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
struct xt_match_param {struct ebt_among_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct ebt_mac_wormhash {int dummy; } ;
struct ebt_among_info {int bitmask; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {char* h_source; char* h_dest; } ;

/* Variables and functions */
 int EBT_AMONG_DST_NEG ; 
 int EBT_AMONG_SRC_NEG ; 
 struct ebt_mac_wormhash* ebt_among_wh_dst (struct ebt_among_info const*) ; 
 struct ebt_mac_wormhash* ebt_among_wh_src (struct ebt_among_info const*) ; 
 scalar_t__ ebt_mac_wormhash_contains (struct ebt_mac_wormhash const*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* eth_hdr (struct sk_buff const*) ; 
 scalar_t__ get_ip_dst (struct sk_buff const*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_ip_src (struct sk_buff const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ebt_among_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct ebt_among_info *info = par->matchinfo;
	const char *dmac, *smac;
	const struct ebt_mac_wormhash *wh_dst, *wh_src;
	__be32 dip = 0, sip = 0;

	wh_dst = ebt_among_wh_dst(info);
	wh_src = ebt_among_wh_src(info);

	if (wh_src) {
		smac = eth_hdr(skb)->h_source;
		if (get_ip_src(skb, &sip))
			return false;
		if (!(info->bitmask & EBT_AMONG_SRC_NEG)) {
			/* we match only if it contains */
			if (!ebt_mac_wormhash_contains(wh_src, smac, sip))
				return false;
		} else {
			/* we match only if it DOES NOT contain */
			if (ebt_mac_wormhash_contains(wh_src, smac, sip))
				return false;
		}
	}

	if (wh_dst) {
		dmac = eth_hdr(skb)->h_dest;
		if (get_ip_dst(skb, &dip))
			return false;
		if (!(info->bitmask & EBT_AMONG_DST_NEG)) {
			/* we match only if it contains */
			if (!ebt_mac_wormhash_contains(wh_dst, dmac, dip))
				return false;
		} else {
			/* we match only if it DOES NOT contain */
			if (ebt_mac_wormhash_contains(wh_dst, dmac, dip))
				return false;
		}
	}

	return true;
}