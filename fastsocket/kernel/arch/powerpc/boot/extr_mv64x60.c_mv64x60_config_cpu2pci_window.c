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
typedef  size_t u8 ;
typedef  int u32 ;
struct mv64x60_cpu2pci_win {int lo; scalar_t__ remap_hi; int remap_lo; int size; } ;

/* Variables and functions */
 int MV64x60_CPU2PCI_SWAP_NONE ; 
 int /*<<< orphan*/  out_le32 (int*,int) ; 

void mv64x60_config_cpu2pci_window(u8 *bridge_base, u8 hose, u32 pci_base_hi,
		u32 pci_base_lo, u32 cpu_base, u32 size,
		struct mv64x60_cpu2pci_win *offset_tbl)
{
	cpu_base >>= 16;
	cpu_base |= MV64x60_CPU2PCI_SWAP_NONE;
	out_le32((u32 *)(bridge_base + offset_tbl[hose].lo), cpu_base);

	if (offset_tbl[hose].remap_hi != 0)
		out_le32((u32 *)(bridge_base + offset_tbl[hose].remap_hi),
				pci_base_hi);
	out_le32((u32 *)(bridge_base + offset_tbl[hose].remap_lo),
			pci_base_lo >> 16);

	size = (size - 1) >> 16;
	out_le32((u32 *)(bridge_base + offset_tbl[hose].size), size);
}