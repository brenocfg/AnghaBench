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
 int /*<<< orphan*/  MSC01_IC_DISH ; 
 int /*<<< orphan*/  MSC01_IC_DISL ; 
 int /*<<< orphan*/  MSCIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int irq_base ; 

__attribute__((used)) static inline void mask_msc_irq(unsigned int irq)
{
	if (irq < (irq_base + 32))
		MSCIC_WRITE(MSC01_IC_DISL, 1<<(irq - irq_base));
	else
		MSCIC_WRITE(MSC01_IC_DISH, 1<<(irq - irq_base - 32));
}