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
 scalar_t__ __raw_readl (scalar_t__) ; 
 scalar_t__* edmacc_regs_base ; 

__attribute__((used)) static inline unsigned int edma_read(unsigned ctlr, int offset)
{
	return (unsigned int)__raw_readl(edmacc_regs_base[ctlr] + offset);
}