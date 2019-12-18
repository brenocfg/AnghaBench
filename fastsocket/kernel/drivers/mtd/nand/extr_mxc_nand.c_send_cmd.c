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
typedef  int /*<<< orphan*/  uint16_t ;
struct mxc_nand_host {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL3 ; 
 int /*<<< orphan*/  NFC_CMD ; 
 scalar_t__ NFC_CONFIG2 ; 
 scalar_t__ NFC_FLASH_CMD ; 
 int /*<<< orphan*/  TROP_US_DELAY ; 
 int /*<<< orphan*/  wait_op_done (struct mxc_nand_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void send_cmd(struct mxc_nand_host *host, uint16_t cmd, int useirq)
{
	DEBUG(MTD_DEBUG_LEVEL3, "send_cmd(host, 0x%x, %d)\n", cmd, useirq);

	writew(cmd, host->regs + NFC_FLASH_CMD);
	writew(NFC_CMD, host->regs + NFC_CONFIG2);

	/* Wait for operation to complete */
	wait_op_done(host, TROP_US_DELAY, cmd, useirq);
}