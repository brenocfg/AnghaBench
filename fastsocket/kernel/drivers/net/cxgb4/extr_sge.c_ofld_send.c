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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ofldtxq; int /*<<< orphan*/ * ctrlq; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int ctrl_xmit (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  is_ctrl_pkt (struct sk_buff*) ; 
 int ofld_xmit (int /*<<< orphan*/ *,struct sk_buff*) ; 
 unsigned int skb_txq (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ofld_send(struct adapter *adap, struct sk_buff *skb)
{
	unsigned int idx = skb_txq(skb);

	if (unlikely(is_ctrl_pkt(skb)))
		return ctrl_xmit(&adap->sge.ctrlq[idx], skb);
	return ofld_xmit(&adap->sge.ofldtxq[idx], skb);
}