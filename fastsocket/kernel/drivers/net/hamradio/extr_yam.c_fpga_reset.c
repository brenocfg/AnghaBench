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

/* Variables and functions */
 int /*<<< orphan*/  DLL (int) ; 
 int /*<<< orphan*/  DLM (int) ; 
 int /*<<< orphan*/  IER (int) ; 
 int /*<<< orphan*/  LCR (int) ; 
 int LCR_BIT5 ; 
 int LCR_DLAB ; 
 int /*<<< orphan*/  LSR (int) ; 
 int /*<<< orphan*/  MCR (int) ; 
 int MCR_DTR ; 
 int MCR_OUT1 ; 
 int MCR_OUT2 ; 
 int MCR_RTS ; 
 int /*<<< orphan*/  MSR (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fpga_reset(int iobase)
{
	outb(0, IER(iobase));
	outb(LCR_DLAB | LCR_BIT5, LCR(iobase));
	outb(1, DLL(iobase));
	outb(0, DLM(iobase));

	outb(LCR_BIT5, LCR(iobase));
	inb(LSR(iobase));
	inb(MSR(iobase));
	/* turn off FPGA supply voltage */
	outb(MCR_OUT1 | MCR_OUT2, MCR(iobase));
	delay(100);
	/* turn on FPGA supply voltage again */
	outb(MCR_DTR | MCR_RTS | MCR_OUT1 | MCR_OUT2, MCR(iobase));
	delay(100);
}