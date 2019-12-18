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
struct pcf50633 {int /*<<< orphan*/  irq_work; int /*<<< orphan*/  work_queue; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pcf50633_irq(int irq, void *data)
{
	struct pcf50633 *pcf = data;

	dev_dbg(pcf->dev, "pcf50633_irq\n");

	get_device(pcf->dev);
	disable_irq_nosync(pcf->irq);
	queue_work(pcf->work_queue, &pcf->irq_work);

	return IRQ_HANDLED;
}