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
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct TYPE_2__ {int intr_enable_bits; scalar_t__ main_iobase; } ;

/* Variables and functions */
 int ADC_INTR_SRC_MASK ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*,int) ; 
 int EN_ADC_ACTIVE_INTR_BIT ; 
 int EN_ADC_DONE_INTR_BIT ; 
 int EN_ADC_INTR_SRC_BIT ; 
 int EN_ADC_OVERRUN_BIT ; 
 int EN_ADC_STOP_INTR_BIT ; 
 scalar_t__ INTR_ENABLE_REG ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void disable_ai_interrupts(struct comedi_device *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	priv(dev)->intr_enable_bits &=
	    ~EN_ADC_INTR_SRC_BIT & ~EN_ADC_DONE_INTR_BIT &
	    ~EN_ADC_ACTIVE_INTR_BIT & ~EN_ADC_STOP_INTR_BIT &
	    ~EN_ADC_OVERRUN_BIT & ~ADC_INTR_SRC_MASK;
	writew(priv(dev)->intr_enable_bits,
	       priv(dev)->main_iobase + INTR_ENABLE_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	DEBUG_PRINT("intr enable bits 0x%x\n", priv(dev)->intr_enable_bits);
}