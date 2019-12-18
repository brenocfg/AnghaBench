#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vgastate {int dummy; } ;
struct fb_info {struct arkfb_info* par; } ;
struct TYPE_3__ {int flags; int num_crtc; int num_seq; } ;
struct arkfb_info {scalar_t__ ref_count; int /*<<< orphan*/  open_lock; TYPE_1__ state; } ;

/* Variables and functions */
 int VGA_SAVE_CMAP ; 
 int VGA_SAVE_FONTS ; 
 int VGA_SAVE_MODE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_vga (TYPE_1__*) ; 

__attribute__((used)) static int arkfb_open(struct fb_info *info, int user)
{
	struct arkfb_info *par = info->par;

	mutex_lock(&(par->open_lock));
	if (par->ref_count == 0) {
		memset(&(par->state), 0, sizeof(struct vgastate));
		par->state.flags = VGA_SAVE_MODE | VGA_SAVE_FONTS | VGA_SAVE_CMAP;
		par->state.num_crtc = 0x60;
		par->state.num_seq = 0x30;
		save_vga(&(par->state));
	}

	par->ref_count++;
	mutex_unlock(&(par->open_lock));

	return 0;
}