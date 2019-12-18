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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct amd8131_dev_info {struct pci_dev* dev; } ;

/* Variables and functions */
 int INT_CTLR_DTSE ; 
 int INT_CTLR_PERR ; 
 int INT_CTLR_SERR ; 
 int LNK_CTRL_CRCFEN ; 
 int /*<<< orphan*/  REG_INT_CTLR ; 
 int /*<<< orphan*/  REG_LNK_CTRL_A ; 
 int /*<<< orphan*/  REG_LNK_CTRL_B ; 
 int /*<<< orphan*/  REG_STS_CMD ; 
 int STS_CMD_SERREN ; 
 int /*<<< orphan*/  edac_pci_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  edac_pci_write_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amd8131_pcix_exit(struct amd8131_dev_info *dev_info)
{
	u32 val32;
	struct pci_dev *dev = dev_info->dev;

	/* Disable SERR, PERR and DTSE Error detection */
	edac_pci_read_dword(dev, REG_INT_CTLR, &val32);
	val32 &= ~(INT_CTLR_PERR | INT_CTLR_SERR | INT_CTLR_DTSE);
	edac_pci_write_dword(dev, REG_INT_CTLR, val32);

	/* Disable overall System Error detection */
	edac_pci_read_dword(dev, REG_STS_CMD, &val32);
	val32 &= ~STS_CMD_SERREN;
	edac_pci_write_dword(dev, REG_STS_CMD, val32);

	/* Disable CRC Sync Flood on link side A */
	edac_pci_read_dword(dev, REG_LNK_CTRL_A, &val32);
	val32 &= ~LNK_CTRL_CRCFEN;
	edac_pci_write_dword(dev, REG_LNK_CTRL_A, val32);

	/* Disable CRC Sync Flood on link side B */
	edac_pci_read_dword(dev, REG_LNK_CTRL_B, &val32);
	val32 &= ~LNK_CTRL_CRCFEN;
	edac_pci_write_dword(dev, REG_LNK_CTRL_B, val32);
}