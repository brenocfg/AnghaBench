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
struct TYPE_2__ {int fir_base; scalar_t__ speed; } ;
struct w83977af_ir {TYPE_1__ io; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int __u8 ;

/* Variables and functions */
 scalar_t__ ICR ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 scalar_t__ ISR ; 
 scalar_t__ PIO_MAX_SPEED ; 
 int /*<<< orphan*/  SET0 ; 
 scalar_t__ SSR ; 
 int inb (scalar_t__) ; 
 struct w83977af_ir* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  switch_bank (int,int /*<<< orphan*/ ) ; 
 int w83977af_fir_interrupt (struct w83977af_ir*,int) ; 
 int w83977af_sir_interrupt (struct w83977af_ir*,int) ; 

__attribute__((used)) static irqreturn_t w83977af_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct w83977af_ir *self;
	__u8 set, icr, isr;
	int iobase;

	self = netdev_priv(dev);

	iobase = self->io.fir_base;

	/* Save current bank */
	set = inb(iobase+SSR);
	switch_bank(iobase, SET0);
	
	icr = inb(iobase+ICR); 
	isr = inb(iobase+ISR) & icr; /* Mask out the interesting ones */ 

	outb(0, iobase+ICR); /* Disable interrupts */
	
	if (isr) {
		/* Dispatch interrupt handler for the current speed */
		if (self->io.speed > PIO_MAX_SPEED )
			icr = w83977af_fir_interrupt(self, isr);
		else
			icr = w83977af_sir_interrupt(self, isr);
	}

	outb(icr, iobase+ICR);    /* Restore (new) interrupts */
	outb(set, iobase+SSR);    /* Restore bank register */
	return IRQ_RETVAL(isr);
}