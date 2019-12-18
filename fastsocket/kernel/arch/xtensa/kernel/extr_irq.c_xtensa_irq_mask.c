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
 int /*<<< orphan*/  INTENABLE ; 
 int cached_irq_mask ; 
 int /*<<< orphan*/  set_sr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xtensa_irq_mask(unsigned int irq)
{
	cached_irq_mask &= ~(1 << irq);
	set_sr (cached_irq_mask, INTENABLE);
}