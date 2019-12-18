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
struct stlpanel {int dummy; } ;

/* Variables and functions */
 scalar_t__ EREG_DATA ; 
 scalar_t__ SVRR ; 
 unsigned char SVRR_MDM ; 
 unsigned char SVRR_RX ; 
 unsigned char SVRR_TX ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlpanel*,unsigned int) ; 
 int /*<<< orphan*/  stl_cd1400mdmisr (struct stlpanel*,unsigned int) ; 
 int /*<<< orphan*/  stl_cd1400rxisr (struct stlpanel*,unsigned int) ; 
 int /*<<< orphan*/  stl_cd1400txisr (struct stlpanel*,unsigned int) ; 

__attribute__((used)) static void stl_cd1400echintr(struct stlpanel *panelp, unsigned int iobase)
{
	unsigned char	svrtype;

	pr_debug("stl_cd1400echintr(panelp=%p,iobase=%x)\n", panelp, iobase);

	outb(SVRR, iobase);
	svrtype = inb(iobase + EREG_DATA);
	outb((SVRR + 0x80), iobase);
	svrtype |= inb(iobase + EREG_DATA);
	if (svrtype & SVRR_RX)
		stl_cd1400rxisr(panelp, iobase);
	else if (svrtype & SVRR_TX)
		stl_cd1400txisr(panelp, iobase);
	else if (svrtype & SVRR_MDM)
		stl_cd1400mdmisr(panelp, iobase);
}