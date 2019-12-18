#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* qs; } ;
struct adapter {TYPE_2__ sge; } ;
struct TYPE_3__ {int /*<<< orphan*/ * txq; } ;

/* Variables and functions */
 size_t TXQ_CTRL ; 
 int ctrl_xmit (struct adapter*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

int t3_mgmt_tx(struct adapter *adap, struct sk_buff *skb)
{
	int ret;
	local_bh_disable();
	ret = ctrl_xmit(adap, &adap->sge.qs[0].txq[TXQ_CTRL], skb);
	local_bh_enable();

	return ret;
}