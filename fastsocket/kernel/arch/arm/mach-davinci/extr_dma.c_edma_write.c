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
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__* edmacc_regs_base ; 

__attribute__((used)) static inline void edma_write(unsigned ctlr, int offset, int val)
{
	__raw_writel(val, edmacc_regs_base[ctlr] + offset);
}