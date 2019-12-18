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
struct omap_mcbsp_platform_data {int dummy; } ;

/* Variables and functions */

void omap_mcbsp_register_board_cfg(struct omap_mcbsp_platform_data *config,
					int size)
{  }