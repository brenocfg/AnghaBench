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
 scalar_t__* CA91CX42_V_STATID ; 
 TYPE_3__* ca91cx42_bridge ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 

__attribute__((used)) static u32 ca91cx42_VIRQ_irqhandler(int stat)
{
	int vec, i, serviced = 0;
	void (*call)(int, int, void *);
	void *priv_data;

	for (i = 7; i > 0; i--) {
		if (stat & (1 << i)) {
			vec = ioread32(ca91cx42_bridge->base +
				CA91CX42_V_STATID[i]) & 0xff;

			call = ca91cx42_bridge->irq[i - 1].callback[vec].func;
			priv_data =
			ca91cx42_bridge->irq[i - 1].callback[vec].priv_data;

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