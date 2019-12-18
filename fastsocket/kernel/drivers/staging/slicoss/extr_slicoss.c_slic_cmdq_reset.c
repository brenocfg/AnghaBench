#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct slic_hostcmd {struct slic_hostcmd* next_all; struct slic_hostcmd* next; struct sk_buff* skb; scalar_t__ busy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {scalar_t__ count; TYPE_5__ lock; struct slic_hostcmd* head; int /*<<< orphan*/ * tail; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {scalar_t__ count; TYPE_3__ lock; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct TYPE_8__ {scalar_t__ count; struct slic_hostcmd* head; } ;
struct adapter {TYPE_6__ cmdq_free; TYPE_4__ cmdq_done; TYPE_2__ cmdq_all; TYPE_1__* netdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slic_cmdq_reset(struct adapter *adapter)
{
	struct slic_hostcmd *hcmd;
	struct sk_buff *skb;
	u32 outstanding;

	spin_lock_irqsave(&adapter->cmdq_free.lock.lock,
			adapter->cmdq_free.lock.flags);
	spin_lock_irqsave(&adapter->cmdq_done.lock.lock,
			adapter->cmdq_done.lock.flags);
	outstanding = adapter->cmdq_all.count - adapter->cmdq_done.count;
	outstanding -= adapter->cmdq_free.count;
	hcmd = adapter->cmdq_all.head;
	while (hcmd) {
		if (hcmd->busy) {
			skb = hcmd->skb;
			ASSERT(skb);
			hcmd->busy = 0;
			hcmd->skb = NULL;
			dev_kfree_skb_irq(skb);
		}
		hcmd = hcmd->next_all;
	}
	adapter->cmdq_free.count = 0;
	adapter->cmdq_free.head = NULL;
	adapter->cmdq_free.tail = NULL;
	adapter->cmdq_done.count = 0;
	adapter->cmdq_done.head = NULL;
	adapter->cmdq_done.tail = NULL;
	adapter->cmdq_free.head = adapter->cmdq_all.head;
	hcmd = adapter->cmdq_all.head;
	while (hcmd) {
		adapter->cmdq_free.count++;
		hcmd->next = hcmd->next_all;
		hcmd = hcmd->next_all;
	}
	if (adapter->cmdq_free.count != adapter->cmdq_all.count) {
		dev_err(&adapter->netdev->dev,
			"free_count %d != all count %d\n",
			adapter->cmdq_free.count, adapter->cmdq_all.count);
	}
	spin_unlock_irqrestore(&adapter->cmdq_done.lock.lock,
				adapter->cmdq_done.lock.flags);
	spin_unlock_irqrestore(&adapter->cmdq_free.lock.lock,
				adapter->cmdq_free.lock.flags);
}