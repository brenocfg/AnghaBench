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
typedef  int u32 ;
struct TYPE_6__ {TYPE_2__* irq; scalar_t__ base; } ;
struct TYPE_5__ {TYPE_1__* callback; } ;
struct TYPE_4__ {void (* func ) (int,int,void*) ;void* priv_data; } ;

/* Variables and functions */
 scalar_t__* TSI148_LCSR_VIACK ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 TYPE_3__* tsi148_bridge ; 

__attribute__((used)) static u32 tsi148_VIRQ_irqhandler(u32 stat)
{
	int vec, i, serviced = 0;
	void (*call)(int, int, void *);
	void *priv_data;

	for (i = 7; i > 0; i--) {
		if (stat & (1 << i)) {
			/*
			 * 	Note:   Even though the registers are defined
			 * 	as 32-bits in the spec, we only want to issue
			 * 	8-bit IACK cycles on the bus, read from offset
			 * 	3.
			 */
			vec = ioread8(tsi148_bridge->base +
				TSI148_LCSR_VIACK[i] + 3);

			call = tsi148_bridge->irq[i - 1].callback[vec].func;
			priv_data =
				tsi148_bridge->irq[i-1].callback[vec].priv_data;

			if (call != NULL)
				call(i, vec, priv_data);
			else
				printk("Spurilous VME interrupt, level:%x, "
					"vector:%x\n", i, vec);

			serviced |= (1 << i);
		}
	}

	return serviced;
}