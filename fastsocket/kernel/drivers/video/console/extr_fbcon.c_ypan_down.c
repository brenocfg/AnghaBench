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
struct TYPE_3__ {int height; } ;
struct vc_data {size_t vc_num; TYPE_1__ vc_font; scalar_t__ vc_rows; int /*<<< orphan*/  vc_cols; } ;
struct TYPE_4__ {int yoffset; int /*<<< orphan*/  vmode; scalar_t__ xoffset; } ;
struct fbcon_ops {int /*<<< orphan*/  (* update_start ) (struct fb_info*) ;TYPE_2__ var; int /*<<< orphan*/  (* bmove ) (struct vc_data*,struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct fb_info {struct fbcon_ops* fbcon_par; } ;
struct display {int yscroll; scalar_t__ vrows; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VMODE_YWRAP ; 
 size_t* con2fb_map ; 
 struct display* fb_display ; 
 int /*<<< orphan*/  fbcon_clear_margins (struct vc_data*,int) ; 
 struct fb_info** registered_fb ; 
 scalar_t__ scrollback_current ; 
 scalar_t__ scrollback_max ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fb_info*) ; 

__attribute__((used)) static __inline__ void ypan_down(struct vc_data *vc, int count)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct display *p = &fb_display[vc->vc_num];
	struct fbcon_ops *ops = info->fbcon_par;
	
	p->yscroll -= count;
	if (p->yscroll < 0) {
		ops->bmove(vc, info, 0, 0, p->vrows - vc->vc_rows,
			    0, vc->vc_rows, vc->vc_cols);
		p->yscroll += p->vrows - vc->vc_rows;
	}

	ops->var.xoffset = 0;
	ops->var.yoffset = p->yscroll * vc->vc_font.height;
	ops->var.vmode &= ~FB_VMODE_YWRAP;
	ops->update_start(info);
	fbcon_clear_margins(vc, 1);
	scrollback_max -= count;
	if (scrollback_max < 0)
		scrollback_max = 0;
	scrollback_current = 0;
}