#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  authq; int /*<<< orphan*/ * scanresults; } ;
typedef  TYPE_1__ hfa384x_t ;

/* Variables and functions */
 scalar_t__ HFA384x_STATE_PREINIT ; 
 scalar_t__ HFA384x_STATE_RUNNING ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  hfa384x_drvr_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

void hfa384x_destroy(hfa384x_t *hw)
{
	struct sk_buff *skb;

	if (hw->state == HFA384x_STATE_RUNNING)
		hfa384x_drvr_stop(hw);
	hw->state = HFA384x_STATE_PREINIT;

	if (hw->scanresults) {
		kfree(hw->scanresults);
		hw->scanresults = NULL;
	}

	/* Now to clean out the auth queue */
	while ((skb = skb_dequeue(&hw->authq)))
		dev_kfree_skb(skb);
}