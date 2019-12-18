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
struct xt_realm_info {int id; int mask; int invert; } ;
struct xt_match_param {struct xt_realm_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct dst_entry {int tclassid; } ;

/* Variables and functions */
 struct dst_entry* skb_dst (struct sk_buff const*) ; 

__attribute__((used)) static bool
realm_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_realm_info *info = par->matchinfo;
	const struct dst_entry *dst = skb_dst(skb);

	return (info->id == (dst->tclassid & info->mask)) ^ info->invert;
}