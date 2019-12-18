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
struct stlport {int dummy; } ;
struct stlpanel {struct stlport** ports; } ;

/* Variables and functions */
 unsigned int IVR_CHANMASK ; 
 unsigned int IVR_RXDATA ; 
 unsigned int IVR_TXDATA ; 
 scalar_t__ XP_IACK ; 
 int /*<<< orphan*/  brd_lock ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stl_sc26198otherisr (struct stlport*,unsigned int) ; 
 int /*<<< orphan*/  stl_sc26198rxisr (struct stlport*,unsigned int) ; 
 int /*<<< orphan*/  stl_sc26198txisr (struct stlport*) ; 

__attribute__((used)) static void stl_sc26198intr(struct stlpanel *panelp, unsigned int iobase)
{
	struct stlport	*portp;
	unsigned int	iack;

	spin_lock(&brd_lock);

/* 
 *	Work around bug in sc26198 chip... Cannot have A6 address
 *	line of UART high, else iack will be returned as 0.
 */
	outb(0, (iobase + 1));

	iack = inb(iobase + XP_IACK);
	portp = panelp->ports[(iack & IVR_CHANMASK) + ((iobase & 0x4) << 1)];

	if (iack & IVR_RXDATA)
		stl_sc26198rxisr(portp, iack);
	else if (iack & IVR_TXDATA)
		stl_sc26198txisr(portp);
	else
		stl_sc26198otherisr(portp, iack);

	spin_unlock(&brd_lock);
}