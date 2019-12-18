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
struct TYPE_2__ {int /*<<< orphan*/ * par; int /*<<< orphan*/  adapter; } ;
struct savagefb_par {TYPE_1__ chan; } ;
struct fb_info {struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void savagefb_delete_i2c_busses(struct fb_info *info)
{
	struct savagefb_par *par = info->par;

	if (par->chan.par)
		i2c_del_adapter(&par->chan.adapter);

	par->chan.par = NULL;
}