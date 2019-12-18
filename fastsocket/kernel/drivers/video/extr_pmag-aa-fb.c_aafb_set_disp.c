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
typedef  int /*<<< orphan*/  u8 ;
struct fb_fix_screeninfo {int /*<<< orphan*/  line_length; int /*<<< orphan*/  ywrapstep; int /*<<< orphan*/  ypanstep; int /*<<< orphan*/  type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  visual; scalar_t__ smem_start; } ;
struct display {int next_line; int can_soft_blank; int /*<<< orphan*/  scrollmode; scalar_t__ inverse; int /*<<< orphan*/  line_length; int /*<<< orphan*/  ywrapstep; int /*<<< orphan*/  ypanstep; int /*<<< orphan*/  type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  visual; int /*<<< orphan*/ * screen_base; scalar_t__ dispsw_data; int /*<<< orphan*/ * dispsw; TYPE_2__* conp; int /*<<< orphan*/  var; int /*<<< orphan*/ * fb_info; } ;
struct aafb_info {int /*<<< orphan*/  info; } ;
struct TYPE_4__ {TYPE_1__* vc_sw; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* con_cursor ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ERASE ; 
 int /*<<< orphan*/  SCROLL_YREDRAW ; 
 int /*<<< orphan*/  aafb_get_fix (struct fb_fix_screeninfo*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aafb_set_var (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aafb_switch8 ; 
 int /*<<< orphan*/  aafbcon_set_font (struct display*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fontheight (struct display*) ; 
 int /*<<< orphan*/  fontwidth (struct display*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aafb_set_disp(struct display *disp, int con,
			  struct aafb_info *info)
{
	struct fb_fix_screeninfo fix;

	disp->fb_info = &info->info;
	aafb_set_var(&disp->var, con, &info->info);
	if (disp->conp && disp->conp->vc_sw && disp->conp->vc_sw->con_cursor)
		disp->conp->vc_sw->con_cursor(disp->conp, CM_ERASE);
	disp->dispsw = &aafb_switch8;
	disp->dispsw_data = 0;

	aafb_get_fix(&fix, con, &info->info);
	disp->screen_base = (u8 *) fix.smem_start;
	disp->visual = fix.visual;
	disp->type = fix.type;
	disp->type_aux = fix.type_aux;
	disp->ypanstep = fix.ypanstep;
	disp->ywrapstep = fix.ywrapstep;
	disp->line_length = fix.line_length;
	disp->next_line = 2048;
	disp->can_soft_blank = 1;
	disp->inverse = 0;
	disp->scrollmode = SCROLL_YREDRAW;

	aafbcon_set_font(disp, fontwidth(disp), fontheight(disp));
}