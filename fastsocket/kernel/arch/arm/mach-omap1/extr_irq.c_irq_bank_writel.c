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
struct TYPE_2__ {scalar_t__ base_reg; } ;

/* Variables and functions */
 TYPE_1__* irq_banks ; 
 int /*<<< orphan*/  omap_writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void irq_bank_writel(unsigned long value, int bank, int offset)
{
	omap_writel(value, irq_banks[bank].base_reg + offset);
}