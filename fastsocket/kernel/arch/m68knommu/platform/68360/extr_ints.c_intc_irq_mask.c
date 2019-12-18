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
struct TYPE_2__ {int intr_cimr; } ;

/* Variables and functions */
 TYPE_1__* pquicc ; 

__attribute__((used)) static void intc_irq_mask(unsigned int irq)
{
	pquicc->intr_cimr &= ~(1 << irq);
}