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
struct xt_target_param {struct xt_NFQ_info* targinfo; } ;
struct xt_NFQ_info {int /*<<< orphan*/  queuenum; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int NF_QUEUE_NR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
nfqueue_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct xt_NFQ_info *tinfo = par->targinfo;

	return NF_QUEUE_NR(tinfo->queuenum);
}