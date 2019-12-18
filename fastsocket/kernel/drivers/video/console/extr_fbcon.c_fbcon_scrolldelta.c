#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int height; } ;
struct vc_data {size_t vc_num; scalar_t__ vc_mode; int vc_top; scalar_t__ vc_bottom; scalar_t__ vc_rows; int vc_origin; int vc_size_row; int vc_cols; TYPE_3__ vc_font; } ;
struct TYPE_6__ {int yoffset; scalar_t__ xoffset; } ;
struct fbcon_ops {int /*<<< orphan*/  (* update_start ) (struct fb_info*) ;TYPE_2__ var; } ;
struct TYPE_5__ {int /*<<< orphan*/  vmode; } ;
struct fb_info {TYPE_1__ var; struct fbcon_ops* fbcon_par; } ;
struct display {int yscroll; int vrows; int scrollmode; } ;
struct TYPE_8__ {struct vc_data* d; } ;

/* Variables and functions */
 int CM_DRAW ; 
 int CM_ERASE ; 
 int CM_SOFTBACK ; 
 int ENOSYS ; 
 size_t FBCON_LOGO_CANSHOW ; 
 int /*<<< orphan*/  FB_VMODE_YWRAP ; 
 scalar_t__ KD_TEXT ; 
#define  SCROLL_PAN_MOVE 130 
#define  SCROLL_PAN_REDRAW 129 
#define  SCROLL_WRAP_MOVE 128 
 size_t* con2fb_map ; 
 struct display* fb_display ; 
 int /*<<< orphan*/  fbcon_cursor (struct vc_data*,int) ; 
 scalar_t__ fbcon_is_inactive (struct vc_data*,struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_redraw_softback (struct vc_data*,struct display*,int) ; 
 size_t fg_console ; 
 int logo_lines ; 
 size_t logo_shown ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  scr_memcpyw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int scrollback_current ; 
 int scrollback_max ; 
 int /*<<< orphan*/  scrollback_phys_max ; 
 unsigned long softback_buf ; 
 unsigned long softback_curr ; 
 unsigned long softback_end ; 
 unsigned long softback_in ; 
 long softback_top ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 
 int /*<<< orphan*/  update_region (struct vc_data*,int,int) ; 
 TYPE_4__* vc_cons ; 

__attribute__((used)) static int fbcon_scrolldelta(struct vc_data *vc, int lines)
{
	struct fb_info *info = registered_fb[con2fb_map[fg_console]];
	struct fbcon_ops *ops = info->fbcon_par;
	struct display *disp = &fb_display[fg_console];
	int offset, limit, scrollback_old;

	if (softback_top) {
		if (vc->vc_num != fg_console)
			return 0;
		if (vc->vc_mode != KD_TEXT || !lines)
			return 0;
		if (logo_shown >= 0) {
			struct vc_data *conp2 = vc_cons[logo_shown].d;

			if (conp2->vc_top == logo_lines
			    && conp2->vc_bottom == conp2->vc_rows)
				conp2->vc_top = 0;
			if (logo_shown == vc->vc_num) {
				unsigned long p, q;
				int i;

				p = softback_in;
				q = vc->vc_origin +
				    logo_lines * vc->vc_size_row;
				for (i = 0; i < logo_lines; i++) {
					if (p == softback_top)
						break;
					if (p == softback_buf)
						p = softback_end;
					p -= vc->vc_size_row;
					q -= vc->vc_size_row;
					scr_memcpyw((u16 *) q, (u16 *) p,
						    vc->vc_size_row);
				}
				softback_in = softback_curr = p;
				update_region(vc, vc->vc_origin,
					      logo_lines * vc->vc_cols);
			}
			logo_shown = FBCON_LOGO_CANSHOW;
		}
		fbcon_cursor(vc, CM_ERASE | CM_SOFTBACK);
		fbcon_redraw_softback(vc, disp, lines);
		fbcon_cursor(vc, CM_DRAW | CM_SOFTBACK);
		return 0;
	}

	if (!scrollback_phys_max)
		return -ENOSYS;

	scrollback_old = scrollback_current;
	scrollback_current -= lines;
	if (scrollback_current < 0)
		scrollback_current = 0;
	else if (scrollback_current > scrollback_max)
		scrollback_current = scrollback_max;
	if (scrollback_current == scrollback_old)
		return 0;

	if (fbcon_is_inactive(vc, info))
		return 0;

	fbcon_cursor(vc, CM_ERASE);

	offset = disp->yscroll - scrollback_current;
	limit = disp->vrows;
	switch (disp->scrollmode) {
	case SCROLL_WRAP_MOVE:
		info->var.vmode |= FB_VMODE_YWRAP;
		break;
	case SCROLL_PAN_MOVE:
	case SCROLL_PAN_REDRAW:
		limit -= vc->vc_rows;
		info->var.vmode &= ~FB_VMODE_YWRAP;
		break;
	}
	if (offset < 0)
		offset += limit;
	else if (offset >= limit)
		offset -= limit;

	ops->var.xoffset = 0;
	ops->var.yoffset = offset * vc->vc_font.height;
	ops->update_start(info);

	if (!scrollback_current)
		fbcon_cursor(vc, CM_DRAW);
	return 0;
}