#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ppp {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  xq; } ;
struct channel {int /*<<< orphan*/  upl; struct ppp* ppp; TYPE_2__ file; int /*<<< orphan*/  downl; TYPE_3__* chan; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* start_xmit ) (TYPE_3__*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ppp_xmit_process (struct ppp*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct sk_buff*) ; 

__attribute__((used)) static void
ppp_channel_push(struct channel *pch)
{
	struct sk_buff *skb;
	struct ppp *ppp;

	spin_lock_bh(&pch->downl);
	if (pch->chan) {
		while (!skb_queue_empty(&pch->file.xq)) {
			skb = skb_dequeue(&pch->file.xq);
			if (!pch->chan->ops->start_xmit(pch->chan, skb)) {
				/* put the packet back and try again later */
				skb_queue_head(&pch->file.xq, skb);
				break;
			}
		}
	} else {
		/* channel got deregistered */
		skb_queue_purge(&pch->file.xq);
	}
	spin_unlock_bh(&pch->downl);
	/* see if there is anything from the attached unit to be sent */
	if (skb_queue_empty(&pch->file.xq)) {
		read_lock_bh(&pch->upl);
		ppp = pch->ppp;
		if (ppp)
			ppp_xmit_process(ppp);
		read_unlock_bh(&pch->upl);
	}
}