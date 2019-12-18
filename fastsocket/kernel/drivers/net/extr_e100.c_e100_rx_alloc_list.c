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
struct rx {int /*<<< orphan*/  dma_addr; TYPE_3__* skb; struct rx* prev; struct rx* next; } ;
struct rfd {scalar_t__ size; int /*<<< orphan*/  command; } ;
struct TYPE_4__ {unsigned int count; } ;
struct TYPE_5__ {TYPE_1__ rfds; } ;
struct nic {int /*<<< orphan*/  ru_running; struct rx* rxs; struct rx* rx_to_clean; struct rx* rx_to_use; int /*<<< orphan*/  pdev; TYPE_2__ params; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  RU_SUSPENDED ; 
 int /*<<< orphan*/  RU_UNINITIALIZED ; 
 int /*<<< orphan*/  cb_el ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ e100_rx_alloc_skb (struct nic*,struct rx*) ; 
 int /*<<< orphan*/  e100_rx_clean_list (struct nic*) ; 
 struct rx* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e100_rx_alloc_list(struct nic *nic)
{
	struct rx *rx;
	unsigned int i, count = nic->params.rfds.count;
	struct rfd *before_last;

	nic->rx_to_use = nic->rx_to_clean = NULL;
	nic->ru_running = RU_UNINITIALIZED;

	if (!(nic->rxs = kcalloc(count, sizeof(struct rx), GFP_ATOMIC)))
		return -ENOMEM;

	for (rx = nic->rxs, i = 0; i < count; rx++, i++) {
		rx->next = (i + 1 < count) ? rx + 1 : nic->rxs;
		rx->prev = (i == 0) ? nic->rxs + count - 1 : rx - 1;
		if (e100_rx_alloc_skb(nic, rx)) {
			e100_rx_clean_list(nic);
			return -ENOMEM;
		}
	}
	/* Set the el-bit on the buffer that is before the last buffer.
	 * This lets us update the next pointer on the last buffer without
	 * worrying about hardware touching it.
	 * We set the size to 0 to prevent hardware from touching this buffer.
	 * When the hardware hits the before last buffer with el-bit and size
	 * of 0, it will RNR interrupt, the RU will go into the No Resources
	 * state.  It will not complete nor write to this buffer. */
	rx = nic->rxs->prev->prev;
	before_last = (struct rfd *)rx->skb->data;
	before_last->command |= cpu_to_le16(cb_el);
	before_last->size = 0;
	pci_dma_sync_single_for_device(nic->pdev, rx->dma_addr,
		sizeof(struct rfd), PCI_DMA_BIDIRECTIONAL);

	nic->rx_to_use = nic->rx_to_clean = nic->rxs;
	nic->ru_running = RU_SUSPENDED;

	return 0;
}