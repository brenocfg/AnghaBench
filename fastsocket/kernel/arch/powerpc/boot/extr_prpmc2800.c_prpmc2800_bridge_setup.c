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
typedef  int /*<<< orphan*/  v ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct mv64x60_cpu2pci_win {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ MV64x60_CPU_BAR_ENABLE ; 
 int MV64x60_PCI_ACC_CNTL_MBURST_128_BYTES ; 
 int MV64x60_PCI_ACC_CNTL_MBURST_32_BYTES ; 
 int MV64x60_PCI_ACC_CNTL_RDSIZE_256_BYTES ; 
 int MV64x60_PCI_ACC_CNTL_RDSIZE_32_BYTES ; 
 int MV64x60_PCI_ACC_CNTL_SNOOP_NONE ; 
 int MV64x60_PCI_ACC_CNTL_SNOOP_WB ; 
 int MV64x60_PCI_ACC_CNTL_SWAP_NONE ; 
 scalar_t__ bridge_base ; 
 int /*<<< orphan*/  dt_xlate_addr (void*,int*,int,unsigned long*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 void* find_node_by_compatible (int /*<<< orphan*/ *,char*) ; 
 int getprop (void*,char*,int*,int) ; 
 int in_le32 (int*) ; 
 int /*<<< orphan*/  mv64x60_config_cpu2pci_window (scalar_t__,int /*<<< orphan*/ ,int,int,unsigned long,int,struct mv64x60_cpu2pci_win*) ; 
 int /*<<< orphan*/  mv64x60_config_ctlr_windows (scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  mv64x60_config_pci_windows (scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct mv64x60_cpu2pci_win* mv64x60_cpu2pci_io ; 
 struct mv64x60_cpu2pci_win* mv64x60_cpu2pci_mem ; 
 scalar_t__* mv64x60_get_bridge_pbase () ; 
 scalar_t__ mv64x60_is_coherent () ; 
 int /*<<< orphan*/  out_le32 (int*,int) ; 

__attribute__((used)) static void prpmc2800_bridge_setup(u32 mem_size)
{
	u32 i, v[12], enables, acc_bits;
	u32 pci_base_hi, pci_base_lo, size, buf[2];
	unsigned long cpu_base;
	int rc;
	void *devp;
	u8 *bridge_pbase, is_coherent;
	struct mv64x60_cpu2pci_win *tbl;

	bridge_pbase = mv64x60_get_bridge_pbase();
	is_coherent = mv64x60_is_coherent();

	if (is_coherent)
		acc_bits = MV64x60_PCI_ACC_CNTL_SNOOP_WB
			| MV64x60_PCI_ACC_CNTL_SWAP_NONE
			| MV64x60_PCI_ACC_CNTL_MBURST_32_BYTES
			| MV64x60_PCI_ACC_CNTL_RDSIZE_32_BYTES;
	else
		acc_bits = MV64x60_PCI_ACC_CNTL_SNOOP_NONE
			| MV64x60_PCI_ACC_CNTL_SWAP_NONE
			| MV64x60_PCI_ACC_CNTL_MBURST_128_BYTES
			| MV64x60_PCI_ACC_CNTL_RDSIZE_256_BYTES;

	mv64x60_config_ctlr_windows(bridge_base, bridge_pbase, is_coherent);
	mv64x60_config_pci_windows(bridge_base, bridge_pbase, 0, 0, mem_size,
			acc_bits);

	/* Get the cpu -> pci i/o & mem mappings from the device tree */
	devp = find_node_by_compatible(NULL, "marvell,mv64360-pci");
	if (devp == NULL)
		fatal("Error: Missing marvell,mv64360-pci"
				" device tree node\n\r");

	rc = getprop(devp, "ranges", v, sizeof(v));
	if (rc != sizeof(v))
		fatal("Error: Can't find marvell,mv64360-pci ranges"
				" property\n\r");

	/* Get the cpu -> pci i/o & mem mappings from the device tree */
	devp = find_node_by_compatible(NULL, "marvell,mv64360");
	if (devp == NULL)
		fatal("Error: Missing marvell,mv64360 device tree node\n\r");

	enables = in_le32((u32 *)(bridge_base + MV64x60_CPU_BAR_ENABLE));
	enables |= 0x0007fe00; /* Disable all cpu->pci windows */
	out_le32((u32 *)(bridge_base + MV64x60_CPU_BAR_ENABLE), enables);

	for (i=0; i<12; i+=6) {
		switch (v[i] & 0xff000000) {
		case 0x01000000: /* PCI I/O Space */
			tbl = mv64x60_cpu2pci_io;
			break;
		case 0x02000000: /* PCI MEM Space */
			tbl = mv64x60_cpu2pci_mem;
			break;
		default:
			continue;
		}

		pci_base_hi = v[i+1];
		pci_base_lo = v[i+2];
		cpu_base = v[i+3];
		size = v[i+5];

		buf[0] = cpu_base;
		buf[1] = size;

		if (!dt_xlate_addr(devp, buf, sizeof(buf), &cpu_base))
			fatal("Error: Can't translate PCI address 0x%x\n\r",
					(u32)cpu_base);

		mv64x60_config_cpu2pci_window(bridge_base, 0, pci_base_hi,
				pci_base_lo, cpu_base, size, tbl);
	}

	enables &= ~0x00000600; /* Enable cpu->pci0 i/o, cpu->pci0 mem0 */
	out_le32((u32 *)(bridge_base + MV64x60_CPU_BAR_ENABLE), enables);
}