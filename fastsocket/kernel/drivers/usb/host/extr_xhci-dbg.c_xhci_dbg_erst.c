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
typedef  int u64 ;
struct xhci_hcd {int dummy; } ;
struct xhci_erst_entry {int /*<<< orphan*/  rsvd; int /*<<< orphan*/  seg_size; int /*<<< orphan*/  seg_addr; } ;
struct xhci_erst {int erst_dma_addr; int num_entries; struct xhci_erst_entry* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xhci_dbg_erst(struct xhci_hcd *xhci, struct xhci_erst *erst)
{
	u64 addr = erst->erst_dma_addr;
	int i;
	struct xhci_erst_entry *entry;

	for (i = 0; i < erst->num_entries; ++i) {
		entry = &erst->entries[i];
		xhci_dbg(xhci, "@%016llx %08x %08x %08x %08x\n",
			 addr,
			 lower_32_bits(le64_to_cpu(entry->seg_addr)),
			 upper_32_bits(le64_to_cpu(entry->seg_addr)),
			 le32_to_cpu(entry->seg_size),
			 le32_to_cpu(entry->rsvd));
		addr += sizeof(*entry);
	}
}