#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct TYPE_6__ {scalar_t__ layout; TYPE_1__* ai_fifo; } ;
struct TYPE_5__ {int adc_control1_bits; int hw_config_bits; int intr_enable_bits; scalar_t__ main_iobase; int /*<<< orphan*/  dac_control1_bits; int /*<<< orphan*/  fifo_size_bits; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_segment_length; } ;

/* Variables and functions */
 scalar_t__ ADC_CONTROL1_REG ; 
 int ADC_QUEUE_CONFIG_BIT ; 
 scalar_t__ ADC_SAMPLE_INTERVAL_UPPER_REG ; 
 scalar_t__ CALIBRATION_REG ; 
 int /*<<< orphan*/  DAC_FIFO_BITS ; 
 int /*<<< orphan*/  DAC_OUTPUT_ENABLE_BIT ; 
 scalar_t__ DAQ_SYNC_REG ; 
 int DMA_CH_SELECT_BIT ; 
 int EN_DAC_DONE_INTR_BIT ; 
 int EN_DAC_UNDERRUN_BIT ; 
 scalar_t__ HW_CONFIG_REG ; 
 int INTERNAL_CLOCK_4020_BITS ; 
 scalar_t__ INTR_ENABLE_REG ; 
 scalar_t__ LAYOUT_4020 ; 
 int SLOW_DAC_BIT ; 
 TYPE_3__* board (struct comedi_device*) ; 
 int /*<<< orphan*/  disable_ai_pacing (struct comedi_device*) ; 
 TYPE_2__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  set_ai_fifo_segment_length (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void init_stc_registers(struct comedi_device *dev)
{
	uint16_t bits;
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);

	/*  bit should be set for 6025, although docs say boards with <= 16 chans should be cleared XXX */
	if (1)
		priv(dev)->adc_control1_bits |= ADC_QUEUE_CONFIG_BIT;
	writew(priv(dev)->adc_control1_bits,
	       priv(dev)->main_iobase + ADC_CONTROL1_REG);

	/*  6402/16 manual says this register must be initialized to 0xff? */
	writew(0xff, priv(dev)->main_iobase + ADC_SAMPLE_INTERVAL_UPPER_REG);

	bits = SLOW_DAC_BIT | DMA_CH_SELECT_BIT;
	if (board(dev)->layout == LAYOUT_4020)
		bits |= INTERNAL_CLOCK_4020_BITS;
	priv(dev)->hw_config_bits |= bits;
	writew(priv(dev)->hw_config_bits,
	       priv(dev)->main_iobase + HW_CONFIG_REG);

	writew(0, priv(dev)->main_iobase + DAQ_SYNC_REG);
	writew(0, priv(dev)->main_iobase + CALIBRATION_REG);

	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  set fifos to maximum size */
	priv(dev)->fifo_size_bits |= DAC_FIFO_BITS;
	set_ai_fifo_segment_length(dev,
				   board(dev)->ai_fifo->max_segment_length);

	priv(dev)->dac_control1_bits = DAC_OUTPUT_ENABLE_BIT;
	priv(dev)->intr_enable_bits =	/* EN_DAC_INTR_SRC_BIT | DAC_INTR_QEMPTY_BITS | */
	    EN_DAC_DONE_INTR_BIT | EN_DAC_UNDERRUN_BIT;
	writew(priv(dev)->intr_enable_bits,
	       priv(dev)->main_iobase + INTR_ENABLE_REG);

	disable_ai_pacing(dev);
}