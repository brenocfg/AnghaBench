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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQ_FRAMEMASK ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dispc_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ rfbi ; 
 int /*<<< orphan*/  rfbi_dma_callback ; 
 int /*<<< orphan*/  rfbi_put_clocks () ; 

__attribute__((used)) static void rfbi_cleanup(void)
{
	omap_dispc_free_irq(DISPC_IRQ_FRAMEMASK, rfbi_dma_callback, NULL);
	rfbi_put_clocks();
	iounmap(rfbi.base);
}