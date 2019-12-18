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
struct vc_data {int dummy; } ;
struct TYPE_3__ {int cursor_y; int cursor_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ERASE ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  sti_bmove (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  sticon_cursor (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sticon_sti ; 

__attribute__((used)) static void sticon_bmove(struct vc_data *conp, int sy, int sx, 
	int dy, int dx, int height, int width)
{
    if (!width || !height)
	    return;
#if 0
    if (((sy <= p->cursor_y) && (p->cursor_y < sy+height) &&
	(sx <= p->cursor_x) && (p->cursor_x < sx+width)) ||
	((dy <= p->cursor_y) && (p->cursor_y < dy+height) &&
	(dx <= p->cursor_x) && (p->cursor_x < dx+width)))
		sticon_cursor(p, CM_ERASE /*|CM_SOFTBACK*/);
#endif

    sti_bmove(sticon_sti, sy, sx, dy, dx, height, width);
}