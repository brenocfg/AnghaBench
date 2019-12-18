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
struct slgt_info {int rx_restart; int /*<<< orphan*/  pending_bh; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_RECEIVE ; 
 unsigned int BIT4 ; 
 unsigned int BIT5 ; 
 int /*<<< orphan*/  DBGISR (char*) ; 
 int /*<<< orphan*/  RDCSR ; 
 unsigned int rd_reg32 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_reg32 (struct slgt_info*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void isr_rdma(struct slgt_info *info)
{
	unsigned int status = rd_reg32(info, RDCSR);

	DBGISR(("%s isr_rdma status=%08x\n", info->device_name, status));

	/* RDCSR (rx DMA control/status)
	 *
	 * 31..07  reserved
	 * 06      save status byte to DMA buffer
	 * 05      error
	 * 04      eol (end of list)
	 * 03      eob (end of buffer)
	 * 02      IRQ enable
	 * 01      reset
	 * 00      enable
	 */
	wr_reg32(info, RDCSR, status);	/* clear pending */

	if (status & (BIT5 + BIT4)) {
		DBGISR(("%s isr_rdma rx_restart=1\n", info->device_name));
		info->rx_restart = true;
	}
	info->pending_bh |= BH_RECEIVE;
}