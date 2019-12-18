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
 int /*<<< orphan*/  g_osd_y ; 
 int /*<<< orphan*/  layer_fb ; 
 int /*<<< orphan*/  vout_fbdev_clear_lines (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void plat_status_msg_clear(void)
{
	vout_fbdev_clear_lines(layer_fb, g_osd_y, 8);
}