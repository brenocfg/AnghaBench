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
struct ep93xx_fbi {scalar_t__ mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void ep93xxfb_writel(struct ep93xx_fbi *fbi,
				   unsigned int val, unsigned int off)
{
	__raw_writel(val, fbi->mmio_base + off);
}