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
struct b43legacy_pioqueue {int nr_txfree; int /*<<< orphan*/  txfree; struct b43legacy_pio_txpacket* tx_packets_cache; } ;
struct b43legacy_pio_txpacket {int /*<<< orphan*/  list; struct b43legacy_pioqueue* queue; } ;

/* Variables and functions */
 int B43legacy_PIO_MAXTXPACKETS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_txqueues(struct b43legacy_pioqueue *queue)
{
	struct b43legacy_pio_txpacket *packet;
	int i;

	queue->nr_txfree = B43legacy_PIO_MAXTXPACKETS;
	for (i = 0; i < B43legacy_PIO_MAXTXPACKETS; i++) {
		packet = &(queue->tx_packets_cache[i]);

		packet->queue = queue;
		INIT_LIST_HEAD(&packet->list);

		list_add(&packet->list, &queue->txfree);
	}
}