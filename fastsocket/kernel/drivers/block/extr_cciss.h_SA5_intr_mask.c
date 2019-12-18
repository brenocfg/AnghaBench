#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int interrupts_enabled; scalar_t__ vaddr; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  SA5_INTR_OFF ; 
 scalar_t__ SA5_REPLY_INTR_MASK_OFFSET ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void SA5_intr_mask(ctlr_info_t *h, unsigned long val)
{
	if (val) 
	{ /* Turn interrupts on */
		h->interrupts_enabled = 1;
		writel(0, h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	} else /* Turn them off */
	{
		h->interrupts_enabled = 0;
        	writel( SA5_INTR_OFF, 
			h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	}
}