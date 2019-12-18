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
 unsigned int __raw_readl (scalar_t__) ; 
 scalar_t__ davinci_intc_base ; 

__attribute__((used)) static inline unsigned int davinci_irq_readl(int offset)
{
	return __raw_readl(davinci_intc_base + offset);
}