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
struct parisc_device {int /*<<< orphan*/  dev; } ;
struct gsc_fixup_struct {void (* choose_irq ) (struct parisc_device*,void*) ;void* ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct gsc_fixup_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_fixup_irqs_callback ; 

void gsc_fixup_irqs(struct parisc_device *parent, void *ctrl,
			void (*choose_irq)(struct parisc_device *, void *))
{
	struct gsc_fixup_struct data = {
		.choose_irq	= choose_irq,
		.ctrl		= ctrl,
	};

	device_for_each_child(&parent->dev, &data, gsc_fixup_irqs_callback);
}