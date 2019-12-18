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
struct sht15_data {scalar_t__ flag; int /*<<< orphan*/  read_work; int /*<<< orphan*/  interrupt_handled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SHT15_READING_NOTHING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sht15_interrupt_fired(int irq, void *d)
{
	struct sht15_data *data = d;
	/* First disable the interrupt */
	disable_irq_nosync(irq);
	atomic_inc(&data->interrupt_handled);
	/* Then schedule a reading work struct */
	if (data->flag != SHT15_READING_NOTHING)
		schedule_work(&data->read_work);
	return IRQ_HANDLED;
}