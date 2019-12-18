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
 scalar_t__ TSI148_LCSR_VICR ; 
 int TSI148_LCSR_VICR_IRQS ; 
 int ioread32be (scalar_t__) ; 
 TYPE_1__* tsi148_bridge ; 

int tsi148_iack_received(void)
{
	u32 tmp;

	tmp = ioread32be(tsi148_bridge->base + TSI148_LCSR_VICR);

	if (tmp & TSI148_LCSR_VICR_IRQS)
		return 0;
	else
		return 1;
}