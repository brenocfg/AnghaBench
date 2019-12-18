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
struct gem {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ GREG_IMASK ; 
 int /*<<< orphan*/  GREG_STAT_TXDONE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void gem_enable_ints(struct gem *gp)
{
	/* Enable all interrupts but TXDONE */
	writel(GREG_STAT_TXDONE, gp->regs + GREG_IMASK);
}