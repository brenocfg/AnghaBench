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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ MCFSIM_IMR ; 
 scalar_t__ MCF_MBAR ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

void mcf_setimr(int index)
{
	u32 imr;
	imr = __raw_readl(MCF_MBAR + MCFSIM_IMR);
	__raw_writel(imr | (0x1 << index), MCF_MBAR + MCFSIM_IMR);
}