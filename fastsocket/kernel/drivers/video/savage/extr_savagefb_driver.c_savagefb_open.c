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
struct TYPE_5__ {int flags; scalar_t__ vgabase; } ;
struct TYPE_4__ {scalar_t__ vbase; } ;
struct savagefb_par {int /*<<< orphan*/  open_lock; int /*<<< orphan*/  open_count; int /*<<< orphan*/  initial; TYPE_2__ vgastate; TYPE_1__ mmio; } ;
struct fb_info {struct savagefb_par* par; } ;

/* Variables and functions */
 int VGA_SAVE_CMAP ; 
 int VGA_SAVE_FONTS ; 
 int VGA_SAVE_MODE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  savage_get_default_par (struct savagefb_par*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_vga (TYPE_2__*) ; 

__attribute__((used)) static int savagefb_open(struct fb_info *info, int user)
{
	struct savagefb_par *par = info->par;

	mutex_lock(&par->open_lock);

	if (!par->open_count) {
		memset(&par->vgastate, 0, sizeof(par->vgastate));
		par->vgastate.flags = VGA_SAVE_CMAP | VGA_SAVE_FONTS |
			VGA_SAVE_MODE;
		par->vgastate.vgabase = par->mmio.vbase + 0x8000;
		save_vga(&par->vgastate);
		savage_get_default_par(par, &par->initial);
	}

	par->open_count++;
	mutex_unlock(&par->open_lock);
	return 0;
}