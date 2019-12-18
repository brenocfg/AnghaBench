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
struct xt_target_param {int /*<<< orphan*/  targinfo; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  hooknum; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  ipt_ulog_packet (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
ulog_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	ipt_ulog_packet(par->hooknum, skb, par->in, par->out,
	                par->targinfo, NULL);
	return XT_CONTINUE;
}