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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mxc_nand_host {scalar_t__ regs; int /*<<< orphan*/  pagesize_2k; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL3 ; 
 scalar_t__ NFC_BUF_ADDR ; 
 scalar_t__ NFC_CONFIG1 ; 
 scalar_t__ NFC_CONFIG2 ; 
 int /*<<< orphan*/  NFC_OUTPUT ; 
 int /*<<< orphan*/  NFC_SP_EN ; 
 int /*<<< orphan*/  TROP_US_DELAY ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  wait_op_done (struct mxc_nand_host*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void send_read_page(struct mxc_nand_host *host, uint8_t buf_id,
		int spare_only)
{
	DEBUG(MTD_DEBUG_LEVEL3, "send_read_page (%d)\n", spare_only);

	/* NANDFC buffer 0 is used for page read/write */
	writew(buf_id, host->regs + NFC_BUF_ADDR);

	/* Configure spare or page+spare access */
	if (!host->pagesize_2k) {
		uint32_t config1 = readw(host->regs + NFC_CONFIG1);
		if (spare_only)
			config1 |= NFC_SP_EN;
		else
			config1 &= ~NFC_SP_EN;
		writew(config1, host->regs + NFC_CONFIG1);
	}

	writew(NFC_OUTPUT, host->regs + NFC_CONFIG2);

	/* Wait for operation to complete */
	wait_op_done(host, TROP_US_DELAY, spare_only, true);
}