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
struct TYPE_2__ {int xoffset; int yoffset; } ;
struct display {TYPE_1__ var; scalar_t__ fb_info; } ;
struct aafb_cursor {int x; int y; int enable; int /*<<< orphan*/  vbl_cnt; scalar_t__ on; } ;
struct aafb_info {struct aafb_cursor cursor; } ;

/* Variables and functions */
#define  CM_DRAW 130 
#define  CM_ERASE 129 
#define  CM_MOVE 128 
 int /*<<< orphan*/  CURSOR_DRAW_DELAY ; 
 int /*<<< orphan*/  aafb_set_cursor (struct aafb_info*,scalar_t__) ; 
 int fontheight (struct display*) ; 
 int fontwidth (struct display*) ; 

__attribute__((used)) static void aafbcon_cursor(struct display *disp, int mode, int x, int y)
{
	struct aafb_info *info = (struct aafb_info *)disp->fb_info;
	struct aafb_cursor *c = &info->cursor;

	x *= fontwidth(disp);
	y *= fontheight(disp);

	if (c->x == x && c->y == y && (mode == CM_ERASE) == !c->enable)
		return;

	c->enable = 0;
	if (c->on)
		aafb_set_cursor(info, 0);
	c->x = x - disp->var.xoffset;
	c->y = y - disp->var.yoffset;

	switch (mode) {
		case CM_ERASE:
			c->on = 0;
			break;
		case CM_DRAW:
		case CM_MOVE:
			if (c->on)
				aafb_set_cursor(info, c->on);
			else
				c->vbl_cnt = CURSOR_DRAW_DELAY;
			c->enable = 1;
			break;
	}
}