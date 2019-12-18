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
typedef  int u8 ;
struct snd_m3 {int num_substreams; scalar_t__ iobase; TYPE_1__* rmidi; int /*<<< orphan*/  reg_lock; struct m3_dma* substreams; int /*<<< orphan*/  hwvol_tq; } ;
struct m3_dma {scalar_t__ running; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 scalar_t__ ASSP_CONTROL_B ; 
 scalar_t__ ASSP_HOST_INT_STATUS ; 
 int ASSP_INT_PENDING ; 
 int DSP2HOST_REQ_TIMER ; 
 scalar_t__ HOST_INT_STATUS ; 
 int HV_INT_PENDING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MPU401_INT_PENDING ; 
 int STOP_ASSP_CLOCK ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  regs ; 
 int /*<<< orphan*/  snd_m3_update_ptr (struct snd_m3*,struct m3_dma*) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_m3_interrupt(int irq, void *dev_id)
{
	struct snd_m3 *chip = dev_id;
	u8 status;
	int i;

	status = inb(chip->iobase + HOST_INT_STATUS);

	if (status == 0xff)
		return IRQ_NONE;

	if (status & HV_INT_PENDING)
		tasklet_schedule(&chip->hwvol_tq);

	/*
	 * ack an assp int if its running
	 * and has an int pending
	 */
	if (status & ASSP_INT_PENDING) {
		u8 ctl = inb(chip->iobase + ASSP_CONTROL_B);
		if (!(ctl & STOP_ASSP_CLOCK)) {
			ctl = inb(chip->iobase + ASSP_HOST_INT_STATUS);
			if (ctl & DSP2HOST_REQ_TIMER) {
				outb(DSP2HOST_REQ_TIMER, chip->iobase + ASSP_HOST_INT_STATUS);
				/* update adc/dac info if it was a timer int */
				spin_lock(&chip->reg_lock);
				for (i = 0; i < chip->num_substreams; i++) {
					struct m3_dma *s = &chip->substreams[i];
					if (s->running)
						snd_m3_update_ptr(chip, s);
				}
				spin_unlock(&chip->reg_lock);
			}
		}
	}

#if 0 /* TODO: not supported yet */
	if ((status & MPU401_INT_PENDING) && chip->rmidi)
		snd_mpu401_uart_interrupt(irq, chip->rmidi->private_data, regs);
#endif

	/* ack ints */
	outb(status, chip->iobase + HOST_INT_STATUS);

	return IRQ_HANDLED;
}