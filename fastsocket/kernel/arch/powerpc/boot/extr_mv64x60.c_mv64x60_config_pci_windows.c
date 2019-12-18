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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_6__ {int size; int /*<<< orphan*/  lo; int /*<<< orphan*/  fcn; int /*<<< orphan*/  hi; } ;
struct TYPE_5__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_4__ {int lo; int hi; int size; } ;

/* Variables and functions */
 int MV64x60_PCI0_BAR_ENABLE ; 
 int MV64x60_PCI0_PCI_DECODE_CNTL ; 
 int MV64x60_PCI1_BAR_ENABLE ; 
 int MV64x60_PCI1_PCI_DECODE_CNTL ; 
 int MV64x60_PCI_ACC_CNTL_ENABLE ; 
 int MV64x60_PCI_ACC_CNTL_WINDOWS ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int in_le32 (int*) ; 
 int /*<<< orphan*/  mv64x60_cfg_write (int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* mv64x60_pci2mem ; 
 TYPE_2__* mv64x60_pci2reg ; 
 TYPE_1__** mv64x60_pci_acc ; 
 int /*<<< orphan*/  out_le32 (int*,int) ; 

void mv64x60_config_pci_windows(u8 *bridge_base, u8 *bridge_pbase, u8 hose,
		u8 bus, u32 mem_size, u32 acc_bits)
{
	u32 i, offset, bar_enable, enables;

	/* Disable all windows but PCI MEM -> Bridge's regs window */
	enables = ~(1 << 9);
	bar_enable = hose ? MV64x60_PCI1_BAR_ENABLE : MV64x60_PCI0_BAR_ENABLE;
	out_le32((u32 *)(bridge_base + bar_enable), enables);

	for (i=0; i<MV64x60_PCI_ACC_CNTL_WINDOWS; i++)
		out_le32((u32 *)(bridge_base + mv64x60_pci_acc[hose][i].lo), 0);

	/* If mem_size is 0, leave windows disabled */
	if (mem_size == 0)
		return;

	/* Cause automatic updates of PCI remap regs */
	offset = hose ?
		MV64x60_PCI1_PCI_DECODE_CNTL : MV64x60_PCI0_PCI_DECODE_CNTL;
	i = in_le32((u32 *)(bridge_base + offset));
	out_le32((u32 *)(bridge_base + offset), i & ~0x1);

	mem_size = (mem_size - 1) & 0xfffff000;

	/* Map PCI MEM addr 0 -> System Mem addr 0 */
	mv64x60_cfg_write(bridge_base, hose, bus,
			PCI_DEVFN(0, mv64x60_pci2mem[hose].fcn),
			mv64x60_pci2mem[hose].hi, 0);
	mv64x60_cfg_write(bridge_base, hose, bus,
			PCI_DEVFN(0, mv64x60_pci2mem[hose].fcn),
			mv64x60_pci2mem[hose].lo, 0);
	out_le32((u32 *)(bridge_base + mv64x60_pci2mem[hose].size),mem_size);

	acc_bits |= MV64x60_PCI_ACC_CNTL_ENABLE;
	out_le32((u32 *)(bridge_base + mv64x60_pci_acc[hose][0].hi), 0);
	out_le32((u32 *)(bridge_base + mv64x60_pci_acc[hose][0].lo), acc_bits);
	out_le32((u32 *)(bridge_base + mv64x60_pci_acc[hose][0].size),mem_size);

	/* Set PCI MEM->bridge's reg window to where they are in CPU mem map */
	i = (u32)bridge_base;
	i &= 0xffff0000;
	i |= (0x2 << 1);
	mv64x60_cfg_write(bridge_base, hose, bus, PCI_DEVFN(0,0),
			mv64x60_pci2reg[hose].hi, 0);
	mv64x60_cfg_write(bridge_base, hose, bus, PCI_DEVFN(0,0),
			mv64x60_pci2reg[hose].lo, i);

	enables &= ~0x1; /* Enable PCI MEM -> System Mem window 0 */
	out_le32((u32 *)(bridge_base + bar_enable), enables);
}