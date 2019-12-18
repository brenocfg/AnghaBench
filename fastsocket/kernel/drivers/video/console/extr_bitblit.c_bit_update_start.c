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
struct TYPE_4__ {int /*<<< orphan*/  vmode; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct fbcon_ops {TYPE_2__ var; } ;
struct TYPE_3__ {int /*<<< orphan*/  vmode; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct fb_info {TYPE_1__ var; struct fbcon_ops* fbcon_par; } ;

/* Variables and functions */
 int fb_pan_display (struct fb_info*,TYPE_2__*) ; 

__attribute__((used)) static int bit_update_start(struct fb_info *info)
{
	struct fbcon_ops *ops = info->fbcon_par;
	int err;

	err = fb_pan_display(info, &ops->var);
	ops->var.xoffset = info->var.xoffset;
	ops->var.yoffset = info->var.yoffset;
	ops->var.vmode = info->var.vmode;
	return err;
}