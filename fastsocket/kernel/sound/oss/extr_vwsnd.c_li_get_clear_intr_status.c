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
 int /*<<< orphan*/  LI_INTR_MASK ; 
 int /*<<< orphan*/  LI_INTR_STATUS ; 
 unsigned int li_readl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  li_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int li_get_clear_intr_status(lithium_t *lith)
{
	unsigned int status;

	status = li_readl(lith, LI_INTR_STATUS);
	li_writel(lith, LI_INTR_STATUS, ~0);
	return status & li_readl(lith, LI_INTR_MASK);
}