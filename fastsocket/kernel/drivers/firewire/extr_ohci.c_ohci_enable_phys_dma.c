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
struct fw_ohci {int generation; int /*<<< orphan*/  lock; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int ESTALE ; 
 int LOCAL_BUS ; 
 int /*<<< orphan*/  OHCI1394_PhyReqFilterHiSet ; 
 int /*<<< orphan*/  OHCI1394_PhyReqFilterLoSet ; 
 int /*<<< orphan*/  flush_writes (struct fw_ohci*) ; 
 struct fw_ohci* fw_ohci (struct fw_card*) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ohci_enable_phys_dma(struct fw_card *card,
				int node_id, int generation)
{
#ifdef CONFIG_FIREWIRE_OHCI_REMOTE_DMA
	return 0;
#else
	struct fw_ohci *ohci = fw_ohci(card);
	unsigned long flags;
	int n, ret = 0;

	/*
	 * FIXME:  Make sure this bitmask is cleared when we clear the busReset
	 * interrupt bit.  Clear physReqResourceAllBuses on bus reset.
	 */

	spin_lock_irqsave(&ohci->lock, flags);

	if (ohci->generation != generation) {
		ret = -ESTALE;
		goto out;
	}

	/*
	 * Note, if the node ID contains a non-local bus ID, physical DMA is
	 * enabled for _all_ nodes on remote buses.
	 */

	n = (node_id & 0xffc0) == LOCAL_BUS ? node_id & 0x3f : 63;
	if (n < 32)
		reg_write(ohci, OHCI1394_PhyReqFilterLoSet, 1 << n);
	else
		reg_write(ohci, OHCI1394_PhyReqFilterHiSet, 1 << (n - 32));

	flush_writes(ohci);
 out:
	spin_unlock_irqrestore(&ohci->lock, flags);

	return ret;
#endif /* CONFIG_FIREWIRE_OHCI_REMOTE_DMA */
}