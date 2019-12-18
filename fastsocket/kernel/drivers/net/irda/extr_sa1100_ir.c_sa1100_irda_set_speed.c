#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sa1100_irda {int speed; int hscr0; int /*<<< orphan*/  dev; TYPE_1__* pdata; int /*<<< orphan*/  rxdma; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_speed ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int HSCR0_HSSP ; 
 int HSCR0_UART ; 
 int /*<<< orphan*/  IS_FIR (struct sa1100_irda*) ; 
 int Ser2HSCR0 ; 
 int Ser2HSSR0 ; 
 int Ser2UTCR1 ; 
 int Ser2UTCR2 ; 
 int Ser2UTCR3 ; 
 int Ser2UTSR0 ; 
 int UTCR3_RIE ; 
 int UTCR3_RXE ; 
 int UTCR3_TXE ; 
 int UTSR0_RBB ; 
 int UTSR0_REB ; 
 int UTSR0_RID ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sa1100_irda_rx_alloc (struct sa1100_irda*) ; 
 int /*<<< orphan*/  sa1100_irda_rx_dma_start (struct sa1100_irda*) ; 
 int /*<<< orphan*/  sa1100_stop_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sa1100_irda_set_speed(struct sa1100_irda *si, int speed)
{
	unsigned long flags;
	int brd, ret = -EINVAL;

	switch (speed) {
	case 9600:	case 19200:	case 38400:
	case 57600:	case 115200:
		brd = 3686400 / (16 * speed) - 1;

		/*
		 * Stop the receive DMA.
		 */
		if (IS_FIR(si))
			sa1100_stop_dma(si->rxdma);

		local_irq_save(flags);

		Ser2UTCR3 = 0;
		Ser2HSCR0 = HSCR0_UART;

		Ser2UTCR1 = brd >> 8;
		Ser2UTCR2 = brd;

		/*
		 * Clear status register
		 */
		Ser2UTSR0 = UTSR0_REB | UTSR0_RBB | UTSR0_RID;
		Ser2UTCR3 = UTCR3_RIE | UTCR3_RXE | UTCR3_TXE;

		if (si->pdata->set_speed)
			si->pdata->set_speed(si->dev, speed);

		si->speed = speed;

		local_irq_restore(flags);
		ret = 0;
		break;

	case 4000000:
		local_irq_save(flags);

		si->hscr0 = 0;

		Ser2HSSR0 = 0xff;
		Ser2HSCR0 = si->hscr0 | HSCR0_HSSP;
		Ser2UTCR3 = 0;

		si->speed = speed;

		if (si->pdata->set_speed)
			si->pdata->set_speed(si->dev, speed);

		sa1100_irda_rx_alloc(si);
		sa1100_irda_rx_dma_start(si);

		local_irq_restore(flags);

		break;

	default:
		break;
	}

	return ret;
}