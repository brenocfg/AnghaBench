#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_6__ {scalar_t__ menuPosition; int x; int y; int flags; TYPE_1__* parent; } ;
struct TYPE_7__ {int columns; int top; int height; int numitems; int curvalue; int width; int seperation; int /*<<< orphan*/ * itemnames; TYPE_2__ generic; } ;
typedef  TYPE_3__ menulist_s ;
struct TYPE_5__ {scalar_t__ cursor; } ;

/* Variables and functions */
 int QMF_CENTER_JUSTIFY ; 
 scalar_t__ SMALLCHAR_HEIGHT ; 
 int SMALLCHAR_WIDTH ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawString (int,int,int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  UI_FillRect (int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int UI_LEFT ; 
 int UI_PULSE ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  listbar_color ; 
 float* text_color_highlight ; 
 float* text_color_normal ; 

void ScrollList_Draw( menulist_s *l )
{
	int			x;
	int			u;
	int			y;
	int			i;
	int			base;
	int			column;
	float*		color;
	qboolean	hasfocus;
	int			style;

	hasfocus = (l->generic.parent->cursor == l->generic.menuPosition);

	x =	l->generic.x;
	for( column = 0; column < l->columns; column++ ) {
		y =	l->generic.y;
		base = l->top + column * l->height;
		for( i = base; i < base + l->height; i++) {
			if (i >= l->numitems)
				break;

			if (i == l->curvalue)
			{
				u = x - 2;
				if( l->generic.flags & QMF_CENTER_JUSTIFY ) {
					u -= (l->width * SMALLCHAR_WIDTH) / 2 + 1;
				}

				UI_FillRect(u,y,l->width*SMALLCHAR_WIDTH,SMALLCHAR_HEIGHT+2,listbar_color);
				color = text_color_highlight;

				if (hasfocus)
					style = UI_PULSE|UI_LEFT|UI_SMALLFONT;
				else
					style = UI_LEFT|UI_SMALLFONT;
			}
			else
			{
				color = text_color_normal;
				style = UI_LEFT|UI_SMALLFONT;
			}
			if( l->generic.flags & QMF_CENTER_JUSTIFY ) {
				style |= UI_CENTER;
			}

			UI_DrawString(
				x,
				y,
				l->itemnames[i],
				style,
				color);

			y += SMALLCHAR_HEIGHT;
		}
		x += (l->width + l->seperation) * SMALLCHAR_WIDTH;
	}
}