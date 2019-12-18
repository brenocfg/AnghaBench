#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int region_cnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; int /*<<< orphan*/  fbdev; TYPE_1__ mem_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_24XX_DSS_IRQ ; 
 int /*<<< orphan*/  OMAPFB_UPDATE_DISABLED ; 
 int /*<<< orphan*/  cleanup_fbmem () ; 
 TYPE_2__ dispc ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_palette_ram () ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dispc_enable_plane (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dispc_set_update_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_dss_clocks () ; 

__attribute__((used)) static void omap_dispc_cleanup(void)
{
	int i;

	omap_dispc_set_update_mode(OMAPFB_UPDATE_DISABLED);
	/* This will also disable clocks that are on */
	for (i = 0; i < dispc.mem_desc.region_cnt; i++)
		omap_dispc_enable_plane(i, 0);
	cleanup_fbmem();
	free_palette_ram();
	free_irq(INT_24XX_DSS_IRQ, dispc.fbdev);
	put_dss_clocks();
	iounmap(dispc.base);
}