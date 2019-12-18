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
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned int) ; 
 unsigned int cp_intc_base ; 

__attribute__((used)) static inline void cp_intc_write(unsigned long value, unsigned offset)
{
	__raw_writel(value, cp_intc_base + offset);
}