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
struct e1000_ring {unsigned int count; unsigned long size; int /*<<< orphan*/  tail; TYPE_1__* adapter; int /*<<< orphan*/  head; scalar_t__ next_to_clean; scalar_t__ next_to_use; struct e1000_buffer* desc; struct e1000_buffer* buffer_info; } ;
struct e1000_buffer {int dummy; } ;
struct TYPE_2__ {int flags2; } ;

/* Variables and functions */
 int FLAG2_PCIM2PCI_ARBITER_WA ; 
 int /*<<< orphan*/  e1000_put_txbuf (struct e1000_ring*,struct e1000_buffer*) ; 
 int /*<<< orphan*/  e1000e_update_tdt_wa (struct e1000_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct e1000_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_clean_tx_ring(struct e1000_ring *tx_ring)
{
	struct e1000_buffer *buffer_info;
	unsigned long size;
	unsigned int i;

	for (i = 0; i < tx_ring->count; i++) {
		buffer_info = &tx_ring->buffer_info[i];
		e1000_put_txbuf(tx_ring, buffer_info);
	}

	size = sizeof(struct e1000_buffer) * tx_ring->count;
	memset(tx_ring->buffer_info, 0, size);

	memset(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	writel(0, tx_ring->head);
	if (tx_ring->adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
		e1000e_update_tdt_wa(tx_ring, 0);
	else
		writel(0, tx_ring->tail);
}