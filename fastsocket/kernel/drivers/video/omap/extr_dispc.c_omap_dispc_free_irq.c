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
struct TYPE_4__ {TYPE_1__* irq_handlers; } ;
struct TYPE_3__ {void (* callback ) (void*) ;void* data; scalar_t__ irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MAX_IRQ_HANDLERS ; 
 TYPE_2__ dispc ; 
 int /*<<< orphan*/  recalc_irq_mask () ; 

void omap_dispc_free_irq(unsigned long irq_mask, void (*callback)(void *data),
			 void *data)
{
	int i;

	for (i = 0; i < MAX_IRQ_HANDLERS; i++) {
		if (dispc.irq_handlers[i].callback == callback &&
		    dispc.irq_handlers[i].data == data) {
			dispc.irq_handlers[i].irq_mask = 0;
			dispc.irq_handlers[i].callback = NULL;
			dispc.irq_handlers[i].data = NULL;
			recalc_irq_mask();
			return;
		}
	}

	BUG();
}