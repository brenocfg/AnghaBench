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
 unsigned char AUXIO_ORMEIN ; 
 unsigned char AUXIO_ORMEIN4M ; 
 int /*<<< orphan*/  auxio_lock ; 
 int /*<<< orphan*/  auxio_register ; 
 int /*<<< orphan*/  panic (char*) ; 
 unsigned char sbus_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbus_writeb (unsigned char,int /*<<< orphan*/ ) ; 
 int sparc_cpu_model ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
#define  sun4c 130 
#define  sun4d 129 
#define  sun4m 128 

void set_auxio(unsigned char bits_on, unsigned char bits_off)
{
	unsigned char regval;
	unsigned long flags;
	spin_lock_irqsave(&auxio_lock, flags);
	switch(sparc_cpu_model) {
	case sun4c:
		regval = sbus_readb(auxio_register);
		sbus_writeb(((regval | bits_on) & ~bits_off) | AUXIO_ORMEIN,
			auxio_register);
		break;
	case sun4m:
		if(!auxio_register)
			break;     /* VME chassis sun4m, no auxio. */
		regval = sbus_readb(auxio_register);
		sbus_writeb(((regval | bits_on) & ~bits_off) | AUXIO_ORMEIN4M,
			auxio_register);
		break;
	case sun4d:
		break;
	default:
		panic("Can't set AUXIO register on this machine.");
	};
	spin_unlock_irqrestore(&auxio_lock, flags);
}