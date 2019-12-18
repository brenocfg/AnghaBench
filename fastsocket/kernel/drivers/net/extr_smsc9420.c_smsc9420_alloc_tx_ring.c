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
struct smsc9420_ring_info {int dummy; } ;
struct smsc9420_pdata {int /*<<< orphan*/  tx_dma_addr; scalar_t__ tx_ring_tail; scalar_t__ tx_ring_head; TYPE_1__* tx_ring; TYPE_2__* tx_buffers; } ;
struct TYPE_4__ {scalar_t__ mapping; int /*<<< orphan*/ * skb; } ;
struct TYPE_3__ {scalar_t__ length; scalar_t__ buffer2; scalar_t__ buffer1; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFUP ; 
 scalar_t__ TDES1_TER_ ; 
 int /*<<< orphan*/  TX_BASE_ADDR ; 
 int TX_RING_SIZE ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_pci_flush_write (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int smsc9420_alloc_tx_ring(struct smsc9420_pdata *pd)
{
	int i;

	BUG_ON(!pd->tx_ring);

	pd->tx_buffers = kmalloc((sizeof(struct smsc9420_ring_info) *
		TX_RING_SIZE), GFP_KERNEL);
	if (!pd->tx_buffers) {
		smsc_warn(IFUP, "Failed to allocated tx_buffers");
		return -ENOMEM;
	}

	/* Initialize the TX Ring */
	for (i = 0; i < TX_RING_SIZE; i++) {
		pd->tx_buffers[i].skb = NULL;
		pd->tx_buffers[i].mapping = 0;
		pd->tx_ring[i].status = 0;
		pd->tx_ring[i].length = 0;
		pd->tx_ring[i].buffer1 = 0;
		pd->tx_ring[i].buffer2 = 0;
	}
	pd->tx_ring[TX_RING_SIZE - 1].length = TDES1_TER_;
	wmb();

	pd->tx_ring_head = 0;
	pd->tx_ring_tail = 0;

	smsc9420_reg_write(pd, TX_BASE_ADDR, pd->tx_dma_addr);
	smsc9420_pci_flush_write(pd);

	return 0;
}