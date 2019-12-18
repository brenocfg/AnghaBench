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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  width; } ;
struct TYPE_4__ {scalar_t__ rev; TYPE_1__ pci; } ;
struct adapter {TYPE_2__ params; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_CFG ; 
 int /*<<< orphan*/  A_PCIE_MODE ; 
 int /*<<< orphan*/  A_PCIE_PEX_CTRL0 ; 
 int /*<<< orphan*/  A_PCIE_PEX_CTRL1 ; 
 int /*<<< orphan*/  A_PCIE_PEX_ERR ; 
 int F_ENABLELINKDOWNRST ; 
 int F_ENABLELINKDWNDRST ; 
 int F_PCIE_CLIDECEN ; 
 int F_PCIE_DMASTOPEN ; 
 unsigned int G_NUMFSTTRNSEQ (int /*<<< orphan*/ ) ; 
 unsigned int G_NUMFSTTRNSEQRX (int /*<<< orphan*/ ) ; 
 unsigned int M_ACKLAT ; 
 unsigned int M_REPLAYLMT ; 
 unsigned int M_T3A_ACKLAT ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_PAYLOAD ; 
 int PCI_EXP_DEVCTL_READRQ ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int V_ACKLAT (unsigned int) ; 
 int V_REPLAYLMT (unsigned int) ; 
 int V_T3A_ACKLAT (unsigned int) ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void config_pcie(struct adapter *adap)
{
	static const u16 ack_lat[4][6] = {
		{237, 416, 559, 1071, 2095, 4143},
		{128, 217, 289, 545, 1057, 2081},
		{73, 118, 154, 282, 538, 1050},
		{67, 107, 86, 150, 278, 534}
	};
	static const u16 rpl_tmr[4][6] = {
		{711, 1248, 1677, 3213, 6285, 12429},
		{384, 651, 867, 1635, 3171, 6243},
		{219, 354, 462, 846, 1614, 3150},
		{201, 321, 258, 450, 834, 1602}
	};

	u16 val, devid;
	unsigned int log2_width, pldsize;
	unsigned int fst_trn_rx, fst_trn_tx, acklat, rpllmt;

	pcie_capability_read_word(adap->pdev, PCI_EXP_DEVCTL, &val);
	pldsize = (val & PCI_EXP_DEVCTL_PAYLOAD) >> 5;

	pci_read_config_word(adap->pdev, 0x2, &devid);
	if (devid == 0x37) {
		pcie_capability_write_word(adap->pdev, PCI_EXP_DEVCTL,
					   val & ~PCI_EXP_DEVCTL_READRQ &
					   ~PCI_EXP_DEVCTL_PAYLOAD);
		pldsize = 0;
	}

	pcie_capability_read_word(adap->pdev, PCI_EXP_LNKCTL, &val);

	fst_trn_tx = G_NUMFSTTRNSEQ(t3_read_reg(adap, A_PCIE_PEX_CTRL0));
	fst_trn_rx = adap->params.rev == 0 ? fst_trn_tx :
	    G_NUMFSTTRNSEQRX(t3_read_reg(adap, A_PCIE_MODE));
	log2_width = fls(adap->params.pci.width) - 1;
	acklat = ack_lat[log2_width][pldsize];
	if (val & 1)		/* check LOsEnable */
		acklat += fst_trn_tx * 4;
	rpllmt = rpl_tmr[log2_width][pldsize] + fst_trn_rx * 4;

	if (adap->params.rev == 0)
		t3_set_reg_field(adap, A_PCIE_PEX_CTRL1,
				 V_T3A_ACKLAT(M_T3A_ACKLAT),
				 V_T3A_ACKLAT(acklat));
	else
		t3_set_reg_field(adap, A_PCIE_PEX_CTRL1, V_ACKLAT(M_ACKLAT),
				 V_ACKLAT(acklat));

	t3_set_reg_field(adap, A_PCIE_PEX_CTRL0, V_REPLAYLMT(M_REPLAYLMT),
			 V_REPLAYLMT(rpllmt));

	t3_write_reg(adap, A_PCIE_PEX_ERR, 0xffffffff);
	t3_set_reg_field(adap, A_PCIE_CFG, 0,
			 F_ENABLELINKDWNDRST | F_ENABLELINKDOWNRST |
			 F_PCIE_DMASTOPEN | F_PCIE_CLIDECEN);
}