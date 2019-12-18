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
typedef  int uint16_t ;
struct mddi_info {int /*<<< orphan*/  client_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPS ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  CORE_VER ; 
 int /*<<< orphan*/  DISP_WAKE ; 
 int /*<<< orphan*/  DRIVER_START_CNT ; 
 int /*<<< orphan*/  DRIVE_HI ; 
 int /*<<< orphan*/  DRIVE_LO ; 
 int MDDI_CMD_DISP_IGNORE ; 
 int MDDI_CMD_PERIODIC_REV_ENCAP ; 
 int MDDI_HOST_BYTES_PER_SUBFRAME ; 
 int MDDI_HOST_REV_RATE_DIV ; 
 int MDDI_HOST_TA2_LEN ; 
 int /*<<< orphan*/  MDDI_INT_NO_CMD_PKTS_PEND ; 
 int MDDI_MAX_REV_PKT_SIZE ; 
 int MDDI_REV_BUFFER_SIZE ; 
 int /*<<< orphan*/  PAD_CTL ; 
 int /*<<< orphan*/  REV_ENCAP_SZ ; 
 int /*<<< orphan*/  REV_RATE_DIV ; 
 int /*<<< orphan*/  REV_SIZE ; 
 int /*<<< orphan*/  SPM ; 
 int /*<<< orphan*/  TA1_LEN ; 
 int /*<<< orphan*/  TA2_LEN ; 
 int /*<<< orphan*/  VERSION ; 
 int /*<<< orphan*/  mddi_init_rev_encap (struct mddi_info*) ; 
 int mddi_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddi_set_auto_hibernate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddi_wait_interrupt (struct mddi_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddi_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static uint16_t mddi_init_registers(struct mddi_info *mddi)
{
	mddi_writel(0x0001, VERSION);
	mddi_writel(MDDI_HOST_BYTES_PER_SUBFRAME, BPS);
	mddi_writel(0x0003, SPM); /* subframes per media */
	mddi_writel(0x0005, TA1_LEN);
	mddi_writel(MDDI_HOST_TA2_LEN, TA2_LEN);
	mddi_writel(0x0096, DRIVE_HI);
	/* 0x32 normal, 0x50 for Toshiba display */
	mddi_writel(0x0050, DRIVE_LO);
	mddi_writel(0x003C, DISP_WAKE); /* wakeup counter */
	mddi_writel(MDDI_HOST_REV_RATE_DIV, REV_RATE_DIV);

	mddi_writel(MDDI_REV_BUFFER_SIZE, REV_SIZE);
	mddi_writel(MDDI_MAX_REV_PKT_SIZE, REV_ENCAP_SZ);

	/* disable periodic rev encap */
	mddi_writel(MDDI_CMD_PERIODIC_REV_ENCAP, CMD);
	mddi_wait_interrupt(mddi, MDDI_INT_NO_CMD_PKTS_PEND);

	if (mddi_readl(PAD_CTL) == 0) {
		/* If we are turning on band gap, need to wait 5us before
		 * turning on the rest of the PAD */
		mddi_writel(0x08000, PAD_CTL);
		udelay(5);
	}

	/* Recommendation from PAD hw team */
	mddi_writel(0xa850f, PAD_CTL);


	/* Need an even number for counts */
	mddi_writel(0x60006, DRIVER_START_CNT);

	mddi_set_auto_hibernate(&mddi->client_data, 0);

	mddi_writel(MDDI_CMD_DISP_IGNORE, CMD);
	mddi_wait_interrupt(mddi, MDDI_INT_NO_CMD_PKTS_PEND);

	mddi_init_rev_encap(mddi);
	return mddi_readl(CORE_VER) & 0xffff;
}