#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct comedi_cmd {int flags; } ;
struct TYPE_4__ {scalar_t__ layout; } ;
struct TYPE_3__ {int intr_enable_bits; scalar_t__ main_iobase; } ;

/* Variables and functions */
 int ADC_INTR_EOSCAN_BITS ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*,int) ; 
 int EN_ADC_ACTIVE_INTR_BIT ; 
 int EN_ADC_DONE_INTR_BIT ; 
 int EN_ADC_INTR_SRC_BIT ; 
 int EN_ADC_OVERRUN_BIT ; 
 int EN_ADC_STOP_INTR_BIT ; 
 scalar_t__ INTR_ENABLE_REG ; 
 scalar_t__ LAYOUT_4020 ; 
 int TRIG_WAKE_EOS ; 
 TYPE_2__* board (struct comedi_device*) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void enable_ai_interrupts(struct comedi_device *dev,
				 const struct comedi_cmd *cmd)
{
	uint32_t bits;
	unsigned long flags;

	bits = EN_ADC_OVERRUN_BIT | EN_ADC_DONE_INTR_BIT |
	    EN_ADC_ACTIVE_INTR_BIT | EN_ADC_STOP_INTR_BIT;
	/*  Use pio transfer and interrupt on end of conversion if TRIG_WAKE_EOS flag is set. */
	if (cmd->flags & TRIG_WAKE_EOS) {
		/*  4020 doesn't support pio transfers except for fifo dregs */
		if (board(dev)->layout != LAYOUT_4020)
			bits |= ADC_INTR_EOSCAN_BITS | EN_ADC_INTR_SRC_BIT;
	}
	spin_lock_irqsave(&dev->spinlock, flags);
	priv(dev)->intr_enable_bits |= bits;
	writew(priv(dev)->intr_enable_bits,
	       priv(dev)->main_iobase + INTR_ENABLE_REG);
	DEBUG_PRINT("intr enable bits 0x%x\n", priv(dev)->intr_enable_bits);
	spin_unlock_irqrestore(&dev->spinlock, flags);
}