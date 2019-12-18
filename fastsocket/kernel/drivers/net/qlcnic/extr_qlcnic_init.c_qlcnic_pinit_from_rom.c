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
struct qlcnic_adapter {struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct crb_addr_pair {int addr; int data; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCIE_SETUP_FUNCTION ; 
 int /*<<< orphan*/  PCIE_SETUP_FUNCTION2 ; 
 int QLCNIC_ADDR_ERROR ; 
 int QLCNIC_CAM_RAM (int) ; 
 int /*<<< orphan*/  QLCNIC_CMDPEG_STATE ; 
 int QLCNIC_CRB_DDR_NET ; 
 int QLCNIC_CRB_EPG ; 
 int QLCNIC_CRB_I2C0 ; 
 int QLCNIC_CRB_I2Q ; 
 int QLCNIC_CRB_NIU ; 
 int QLCNIC_CRB_PEG_NET_0 ; 
 int QLCNIC_CRB_PEG_NET_1 ; 
 int QLCNIC_CRB_PEG_NET_2 ; 
 int QLCNIC_CRB_PEG_NET_3 ; 
 int QLCNIC_CRB_PEG_NET_4 ; 
 int QLCNIC_CRB_PEG_NET_D ; 
 int QLCNIC_CRB_PEG_NET_I ; 
 int QLCNIC_CRB_SMB ; 
 int QLCNIC_CRB_SRE ; 
 int QLCNIC_CRB_TIMER ; 
 int QLCNIC_PCIE_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ QLCNIC_PCI_CRBSPACE ; 
 int /*<<< orphan*/  QLCNIC_PEG_HALT_STATUS1 ; 
 int /*<<< orphan*/  QLCNIC_PEG_HALT_STATUS2 ; 
 int /*<<< orphan*/  QLCNIC_RCVPEG_STATE ; 
 int QLCNIC_ROMUSB_GLB_SW_RESET ; 
 int QLCRD32 (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  QLCWR32 (struct qlcnic_adapter*,int,int) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ROMUSB_GLB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct crb_addr_pair* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct crb_addr_pair*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int qlcnic_decode_crb_addr (int) ; 
 scalar_t__ qlcnic_rom_fast_read (struct qlcnic_adapter*,int,int*) ; 
 int /*<<< orphan*/  qlcnic_rom_unlock (struct qlcnic_adapter*) ; 

int qlcnic_pinit_from_rom(struct qlcnic_adapter *adapter)
{
	int addr, val;
	int i, n, init_delay;
	struct crb_addr_pair *buf;
	unsigned offset;
	u32 off;
	struct pci_dev *pdev = adapter->pdev;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CMDPEG_STATE, 0);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_RCVPEG_STATE, 0);

	/* Halt all the indiviual PEGs and other blocks */
	/* disable all I2Q */
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x10, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x14, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x18, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x1c, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x20, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x24, 0x0);

	/* disable all niu interrupts */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0x40, 0xff);
	/* disable xge rx/tx */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0x70000, 0x00);
	/* disable xg1 rx/tx */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0x80000, 0x00);
	/* disable sideband mac */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0x90000, 0x00);
	/* disable ap0 mac */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0xa0000, 0x00);
	/* disable ap1 mac */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0xb0000, 0x00);

	/* halt sre */
	val = QLCRD32(adapter, QLCNIC_CRB_SRE + 0x1000);
	QLCWR32(adapter, QLCNIC_CRB_SRE + 0x1000, val & (~(0x1)));

	/* halt epg */
	QLCWR32(adapter, QLCNIC_CRB_EPG + 0x1300, 0x1);

	/* halt timers */
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x0, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x8, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x10, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x18, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x100, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x200, 0x0);
	/* halt pegs */
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_0 + 0x3c, 1);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_1 + 0x3c, 1);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_2 + 0x3c, 1);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_3 + 0x3c, 1);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_4 + 0x3c, 1);
	msleep(20);

	qlcnic_rom_unlock(adapter);
	/* big hammer don't reset CAM block on reset */
	QLCWR32(adapter, QLCNIC_ROMUSB_GLB_SW_RESET, 0xfeffffff);

	/* Init HW CRB block */
	if (qlcnic_rom_fast_read(adapter, 0, &n) != 0 || (n != 0xcafecafe) ||
			qlcnic_rom_fast_read(adapter, 4, &n) != 0) {
		dev_err(&pdev->dev, "ERROR Reading crb_init area: val:%x\n", n);
		return -EIO;
	}
	offset = n & 0xffffU;
	n = (n >> 16) & 0xffffU;

	if (n >= 1024) {
		dev_err(&pdev->dev, "QLOGIC card flash not initialized.\n");
		return -EIO;
	}

	buf = kcalloc(n, sizeof(struct crb_addr_pair), GFP_KERNEL);
	if (buf == NULL) {
		dev_err(&pdev->dev, "Unable to calloc memory for rom read.\n");
		return -ENOMEM;
	}

	for (i = 0; i < n; i++) {
		if (qlcnic_rom_fast_read(adapter, 8*i + 4*offset, &val) != 0 ||
		qlcnic_rom_fast_read(adapter, 8*i + 4*offset + 4, &addr) != 0) {
			kfree(buf);
			return -EIO;
		}

		buf[i].addr = addr;
		buf[i].data = val;
	}

	for (i = 0; i < n; i++) {

		off = qlcnic_decode_crb_addr(buf[i].addr);
		if (off == QLCNIC_ADDR_ERROR) {
			dev_err(&pdev->dev, "CRB init value out of range %x\n",
					buf[i].addr);
			continue;
		}
		off += QLCNIC_PCI_CRBSPACE;

		if (off & 1)
			continue;

		/* skipping cold reboot MAGIC */
		if (off == QLCNIC_CAM_RAM(0x1fc))
			continue;
		if (off == (QLCNIC_CRB_I2C0 + 0x1c))
			continue;
		if (off == (ROMUSB_GLB + 0xbc)) /* do not reset PCI */
			continue;
		if (off == (ROMUSB_GLB + 0xa8))
			continue;
		if (off == (ROMUSB_GLB + 0xc8)) /* core clock */
			continue;
		if (off == (ROMUSB_GLB + 0x24)) /* MN clock */
			continue;
		if (off == (ROMUSB_GLB + 0x1c)) /* MS clock */
			continue;
		if ((off & 0x0ff00000) == QLCNIC_CRB_DDR_NET)
			continue;
		/* skip the function enable register */
		if (off == QLCNIC_PCIE_REG(PCIE_SETUP_FUNCTION))
			continue;
		if (off == QLCNIC_PCIE_REG(PCIE_SETUP_FUNCTION2))
			continue;
		if ((off & 0x0ff00000) == QLCNIC_CRB_SMB)
			continue;

		init_delay = 1;
		/* After writing this register, HW needs time for CRB */
		/* to quiet down (else crb_window returns 0xffffffff) */
		if (off == QLCNIC_ROMUSB_GLB_SW_RESET)
			init_delay = 1000;

		QLCWR32(adapter, off, buf[i].data);

		msleep(init_delay);
	}
	kfree(buf);

	/* Initialize protocol process engine */
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_D + 0xec, 0x1e);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_D + 0x4c, 8);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_I + 0x4c, 8);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_0 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_0 + 0xc, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_1 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_1 + 0xc, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_2 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_2 + 0xc, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_3 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_3 + 0xc, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_4 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_4 + 0xc, 0);
	msleep(1);

	QLC_SHARED_REG_WR32(adapter, QLCNIC_PEG_HALT_STATUS1, 0);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_PEG_HALT_STATUS2, 0);

	return 0;
}