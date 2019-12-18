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
 int /*<<< orphan*/  unmask_irq (unsigned int) ; 

__attribute__((used)) static unsigned int
iosapic_startup_level_irq (unsigned int irq)
{
	unmask_irq(irq);
	return 0;
}