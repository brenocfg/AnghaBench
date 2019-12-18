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
struct xt_tproxy_target_info {int /*<<< orphan*/  mark_value; int /*<<< orphan*/  mark_mask; int /*<<< orphan*/  lport; int /*<<< orphan*/  laddr; } ;
struct xt_target_param {struct xt_tproxy_target_info* targinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int tproxy_tg4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
tproxy_tg4_v0(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct xt_tproxy_target_info *tgi = par->targinfo;

	return tproxy_tg4(skb, tgi->laddr, tgi->lport, tgi->mark_mask, tgi->mark_value);
}