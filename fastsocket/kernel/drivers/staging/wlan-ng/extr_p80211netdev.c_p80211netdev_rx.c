#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rx_bh; int /*<<< orphan*/  nsd_rxq; } ;
typedef  TYPE_1__ wlandevice_t ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void p80211netdev_rx(wlandevice_t *wlandev, struct sk_buff *skb)
{
	/* Enqueue for post-irq processing */
	skb_queue_tail(&wlandev->nsd_rxq, skb);

	tasklet_schedule(&wlandev->rx_bh);

	return;
}