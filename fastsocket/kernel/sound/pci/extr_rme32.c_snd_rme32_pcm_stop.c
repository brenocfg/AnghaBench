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
struct rme32 {int rcreg; int wcreg; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ RME32_IO_CONFIRM_ACTION_IRQ ; 
 scalar_t__ RME32_IO_CONTROL_REGISTER ; 
 scalar_t__ RME32_IO_RESET_POS ; 
 int RME32_RCR_IRQ ; 
 int RME32_WCR_MUTE ; 
 int RME32_WCR_SEL ; 
 int RME32_WCR_START ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void snd_rme32_pcm_stop(struct rme32 * rme32, int to_pause)
{
	/*
	 * Check if there is an unconfirmed IRQ, if so confirm it, or else
	 * the hardware will not stop generating interrupts
	 */
	rme32->rcreg = readl(rme32->iobase + RME32_IO_CONTROL_REGISTER);
	if (rme32->rcreg & RME32_RCR_IRQ) {
		writel(0, rme32->iobase + RME32_IO_CONFIRM_ACTION_IRQ);
	}
	rme32->wcreg &= ~RME32_WCR_START;
	if (rme32->wcreg & RME32_WCR_SEL)
		rme32->wcreg |= RME32_WCR_MUTE;
	writel(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	if (! to_pause)
		writel(0, rme32->iobase + RME32_IO_RESET_POS);
}