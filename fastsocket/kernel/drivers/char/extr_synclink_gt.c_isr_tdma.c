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
struct slgt_info {int /*<<< orphan*/  pending_bh; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_TRANSMIT ; 
 unsigned int BIT3 ; 
 unsigned int BIT4 ; 
 unsigned int BIT5 ; 
 int /*<<< orphan*/  DBGISR (char*) ; 
 int /*<<< orphan*/  TDCSR ; 
 unsigned int rd_reg32 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_reg32 (struct slgt_info*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void isr_tdma(struct slgt_info *info)
{
	unsigned int status = rd_reg32(info, TDCSR);

	DBGISR(("%s isr_tdma status=%08x\n", info->device_name, status));

	/* TDCSR (tx DMA control/status)
	 *
	 * 31..06  reserved
	 * 05      error
	 * 04      eol (end of list)
	 * 03      eob (end of buffer)
	 * 02      IRQ enable
	 * 01      reset
	 * 00      enable
	 */
	wr_reg32(info, TDCSR, status);	/* clear pending */

	if (status & (BIT5 + BIT4 + BIT3)) {
		// another transmit buffer has completed
		// run bottom half to get more send data from user
		info->pending_bh |= BH_TRANSMIT;
	}
}