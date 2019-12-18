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
struct irq_fd {scalar_t__ irq; scalar_t__ id; } ;
struct irq_and_dev {scalar_t__ irq; scalar_t__ dev; } ;

/* Variables and functions */

__attribute__((used)) static int same_irq_and_dev(struct irq_fd *irq, void *d)
{
	struct irq_and_dev *data = d;

	return ((irq->irq == data->irq) && (irq->id == data->dev));
}