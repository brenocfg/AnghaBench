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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int x; int y; int width; int height; int week_start; scalar_t__ window; int /*<<< orphan*/ * parent; int /*<<< orphan*/  box_draw; } ;
typedef  int /*<<< orphan*/  BOX_DRAW ;
typedef  TYPE_1__ BOX ;

/* Variables and functions */
 scalar_t__ KEY_MAX ; 
 scalar_t__ MON_WIDE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ derwin (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  dlg_mouse_mkbigregion (int,scalar_t__,int,scalar_t__,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  dlg_mouse_mkregion (int,int,int,int,int) ; 
 int /*<<< orphan*/  dlg_mouse_setbase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getbegx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getbegy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keypad (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_object(BOX * data,
	    WINDOW *parent,
	    int x, int y,
	    int width, int height,
	    BOX_DRAW box_draw,
	    int key_offset,
	    int code)
{
    data->parent = parent;
    data->x = x;
    data->y = y;
    data->width = width;
    data->height = height;
    data->box_draw = box_draw;
    data->week_start = key_offset;

    data->window = derwin(data->parent,
			  data->height, data->width,
			  data->y, data->x);
    if (data->window == 0)
	return -1;
    (void) keypad(data->window, TRUE);

    dlg_mouse_setbase(getbegx(parent), getbegy(parent));
    if (code == 'D') {
	dlg_mouse_mkbigregion(y + 1, x + MON_WIDE, height - 1, width - MON_WIDE,
			      KEY_MAX + key_offset, 1, MON_WIDE, 3);
    } else {
	dlg_mouse_mkregion(y, x, height, width, code);
    }

    return 0;
}