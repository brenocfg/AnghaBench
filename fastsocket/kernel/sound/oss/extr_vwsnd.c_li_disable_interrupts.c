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
typedef  int /*<<< orphan*/  lithium_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGEV (char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  LI_INTR_MASK ; 
 int /*<<< orphan*/  LI_INTR_STATUS ; 
 unsigned int li_readl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  li_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void li_disable_interrupts(lithium_t *lith, unsigned int mask)
{
	unsigned int keepmask;

	DBGEV("(lith=0x%p, mask=0x%x)\n", lith, mask);

	/* disable the interrupts */

	keepmask = li_readl(lith, LI_INTR_MASK) & ~mask;
	li_writel(lith, LI_INTR_MASK, keepmask);

	/* clear any pending interrupts. */

	li_writel(lith, LI_INTR_STATUS, mask);
}