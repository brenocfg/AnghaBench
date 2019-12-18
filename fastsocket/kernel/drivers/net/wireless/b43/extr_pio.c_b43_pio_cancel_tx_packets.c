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
struct b43_pio_txqueue {TYPE_2__* dev; struct b43_pio_txpacket* packets; } ;
struct b43_pio_txpacket {int /*<<< orphan*/ * skb; } ;
struct TYPE_4__ {TYPE_1__* wl; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct b43_pio_txpacket*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_pio_cancel_tx_packets(struct b43_pio_txqueue *q)
{
	struct b43_pio_txpacket *pack;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(q->packets); i++) {
		pack = &(q->packets[i]);
		if (pack->skb) {
			ieee80211_free_txskb(q->dev->wl->hw, pack->skb);
			pack->skb = NULL;
		}
	}
}