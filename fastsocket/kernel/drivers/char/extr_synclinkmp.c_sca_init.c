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
typedef  int /*<<< orphan*/  SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DMER ; 
 int /*<<< orphan*/  DPCR ; 
 int /*<<< orphan*/  IER0 ; 
 int /*<<< orphan*/  IER1 ; 
 int /*<<< orphan*/  IER2 ; 
 int /*<<< orphan*/  ITCR ; 
 int /*<<< orphan*/  PABR0 ; 
 int /*<<< orphan*/  PABR1 ; 
 int /*<<< orphan*/  WCRH ; 
 int /*<<< orphan*/  WCRL ; 
 int /*<<< orphan*/  WCRM ; 
 int dma_priority ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool sca_init(SLMP_INFO *info)
{
	/* set wait controller to single mem partition (low), no wait states */
	write_reg(info, PABR0, 0);	/* wait controller addr boundary 0 */
	write_reg(info, PABR1, 0);	/* wait controller addr boundary 1 */
	write_reg(info, WCRL, 0);	/* wait controller low range */
	write_reg(info, WCRM, 0);	/* wait controller mid range */
	write_reg(info, WCRH, 0);	/* wait controller high range */

	/* DPCR, DMA Priority Control
	 *
	 * 07..05  Not used, must be 0
	 * 04      BRC, bus release condition: 0=all transfers complete
	 * 03      CCC, channel change condition: 0=every cycle
	 * 02..00  PR<2..0>, priority 100=round robin
	 *
	 * 00000100 = 0x04
	 */
	write_reg(info, DPCR, dma_priority);

	/* DMA Master Enable, BIT7: 1=enable all channels */
	write_reg(info, DMER, 0x80);

	/* enable all interrupt classes */
	write_reg(info, IER0, 0xff);	/* TxRDY,RxRDY,TxINT,RxINT (ports 0-1) */
	write_reg(info, IER1, 0xff);	/* DMIB,DMIA (channels 0-3) */
	write_reg(info, IER2, 0xf0);	/* TIRQ (timers 0-3) */

	/* ITCR, interrupt control register
	 * 07      IPC, interrupt priority, 0=MSCI->DMA
	 * 06..05  IAK<1..0>, Acknowledge cycle, 00=non-ack cycle
	 * 04      VOS, Vector Output, 0=unmodified vector
	 * 03..00  Reserved, must be 0
	 */
	write_reg(info, ITCR, 0);

	return true;
}