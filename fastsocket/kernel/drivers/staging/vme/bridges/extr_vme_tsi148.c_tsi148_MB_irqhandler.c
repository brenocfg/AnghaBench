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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__* TSI148_GCSR_MBOX ; 
 int* TSI148_LCSR_INTC_MBC ; 
 int* TSI148_LCSR_INTS_MBS ; 
 int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 TYPE_1__* tsi148_bridge ; 

__attribute__((used)) static u32 tsi148_MB_irqhandler(u32 stat)
{
	int i;
	u32 val;
	u32 serviced = 0;

	for (i = 0; i < 4; i++) {
		if(stat & TSI148_LCSR_INTS_MBS[i]) {
			val = ioread32be(tsi148_bridge->base +
				TSI148_GCSR_MBOX[i]);
			printk("VME Mailbox %d received: 0x%x\n", i, val);
			serviced |= TSI148_LCSR_INTC_MBC[i];
		}
	}

	return serviced;
}