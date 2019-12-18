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

/* Variables and functions */
 unsigned long MAC_ADDR_HIGH ; 
 unsigned long MAC_ADDR_LOW ; 
 unsigned long MAC_CONTROL ; 
 unsigned long MAC_FLOW_CTRL ; 
 unsigned long MAC_HASH_HIGH ; 
 unsigned long MAC_HASH_LOW ; 
 unsigned long MAC_VLAN1 ; 
 unsigned long MAC_VLAN2 ; 
 unsigned long MMC_CONTROL ; 
 unsigned long MMC_HIGH_INTR ; 
 unsigned long MMC_HIGH_INTR_MASK ; 
 unsigned long MMC_LOW_INTR ; 
 unsigned long MMC_LOW_INTR_MASK ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  readl (unsigned long) ; 

__attribute__((used)) static void mac100_dump_mac_regs(unsigned long ioaddr)
{
	pr_info("\t----------------------------------------------\n"
	       "\t  MAC100 CSR (base addr = 0x%8x)\n"
	       "\t----------------------------------------------\n",
	       (unsigned int)ioaddr);
	pr_info("\tcontrol reg (offset 0x%x): 0x%08x\n", MAC_CONTROL,
	       readl(ioaddr + MAC_CONTROL));
	pr_info("\taddr HI (offset 0x%x): 0x%08x\n ", MAC_ADDR_HIGH,
	       readl(ioaddr + MAC_ADDR_HIGH));
	pr_info("\taddr LO (offset 0x%x): 0x%08x\n", MAC_ADDR_LOW,
	       readl(ioaddr + MAC_ADDR_LOW));
	pr_info("\tmulticast hash HI (offset 0x%x): 0x%08x\n",
			MAC_HASH_HIGH, readl(ioaddr + MAC_HASH_HIGH));
	pr_info("\tmulticast hash LO (offset 0x%x): 0x%08x\n",
			MAC_HASH_LOW, readl(ioaddr + MAC_HASH_LOW));
	pr_info("\tflow control (offset 0x%x): 0x%08x\n",
		MAC_FLOW_CTRL, readl(ioaddr + MAC_FLOW_CTRL));
	pr_info("\tVLAN1 tag (offset 0x%x): 0x%08x\n", MAC_VLAN1,
	       readl(ioaddr + MAC_VLAN1));
	pr_info("\tVLAN2 tag (offset 0x%x): 0x%08x\n", MAC_VLAN2,
	       readl(ioaddr + MAC_VLAN2));
	pr_info("\n\tMAC management counter registers\n");
	pr_info("\t MMC crtl (offset 0x%x): 0x%08x\n",
	       MMC_CONTROL, readl(ioaddr + MMC_CONTROL));
	pr_info("\t MMC High Interrupt (offset 0x%x): 0x%08x\n",
	       MMC_HIGH_INTR, readl(ioaddr + MMC_HIGH_INTR));
	pr_info("\t MMC Low Interrupt (offset 0x%x): 0x%08x\n",
	       MMC_LOW_INTR, readl(ioaddr + MMC_LOW_INTR));
	pr_info("\t MMC High Interrupt Mask (offset 0x%x): 0x%08x\n",
	       MMC_HIGH_INTR_MASK, readl(ioaddr + MMC_HIGH_INTR_MASK));
	pr_info("\t MMC Low Interrupt Mask (offset 0x%x): 0x%08x\n",
	       MMC_LOW_INTR_MASK, readl(ioaddr + MMC_LOW_INTR_MASK));
	return;
}