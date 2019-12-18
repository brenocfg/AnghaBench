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

/* Variables and functions */
 int /*<<< orphan*/  CP_INTC_HOST_ENABLE_IDX_CLR ; 
 int /*<<< orphan*/  CP_INTC_HOST_ENABLE_IDX_SET ; 
 int /*<<< orphan*/  CP_INTC_SYS_ENABLE_IDX_CLR ; 
 int /*<<< orphan*/  cp_intc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cp_intc_mask_irq(unsigned int irq)
{
	/* XXX don't know why we need to disable nIRQ here... */
	cp_intc_write(1, CP_INTC_HOST_ENABLE_IDX_CLR);
	cp_intc_write(irq, CP_INTC_SYS_ENABLE_IDX_CLR);
	cp_intc_write(1, CP_INTC_HOST_ENABLE_IDX_SET);
}