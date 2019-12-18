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
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_PWL_CLK_ENABLE ; 
 int /*<<< orphan*/  OMAP_PWL_ENABLE ; 
 int /*<<< orphan*/  gpio_set_value (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void osk_panel_disable(struct lcd_panel *panel)
{
	/* Set PWL level to zero */
	omap_writeb(0x00, OMAP_PWL_ENABLE);

	/* Disable PWL unit */
	omap_writeb(0x00, OMAP_PWL_CLK_ENABLE);

	/* set GPIO2 low */
	gpio_set_value(2, 0);
}