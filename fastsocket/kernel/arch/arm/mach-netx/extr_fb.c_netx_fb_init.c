#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct clcd_panel {int dummy; } ;
struct clcd_board {int dummy; } ;
struct TYPE_4__ {struct clcd_board* platform_data; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int amba_device_register (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ fb_device ; 
 int /*<<< orphan*/  iomem_resource ; 
 struct clcd_panel* netx_panel ; 

int netx_fb_init(struct clcd_board *board, struct clcd_panel *panel)
{
	netx_panel = panel;
	fb_device.dev.platform_data = board;
	return amba_device_register(&fb_device, &iomem_resource);
}