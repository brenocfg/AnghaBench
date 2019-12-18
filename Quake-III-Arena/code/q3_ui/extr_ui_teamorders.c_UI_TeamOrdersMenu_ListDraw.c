#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_5__ {scalar_t__ menuPosition; int y; TYPE_1__* parent; } ;
struct TYPE_6__ {int numitems; int curvalue; int /*<<< orphan*/ * itemnames; TYPE_2__ generic; } ;
typedef  TYPE_3__ menulist_s ;
struct TYPE_4__ {scalar_t__ cursor; } ;

/* Variables and functions */
 scalar_t__ PROP_HEIGHT ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,int /*<<< orphan*/ ,int,float*) ; 
 int UI_LEFT ; 
 int UI_PULSE ; 
 int UI_SMALLFONT ; 
 float* color_orange ; 
 float* color_yellow ; 

__attribute__((used)) static void UI_TeamOrdersMenu_ListDraw( void *self ) {
	menulist_s	*l;
	int			x;
	int			y;
	int			i;
	float		*color;
	qboolean	hasfocus;
	int			style;

	l = (menulist_s *)self;

	hasfocus = (l->generic.parent->cursor == l->generic.menuPosition);

	x =	320;//l->generic.x;
	y =	l->generic.y;
	for( i = 0; i < l->numitems; i++ ) {
		style = UI_LEFT|UI_SMALLFONT|UI_CENTER;
		if( i == l->curvalue ) {
			color = color_yellow;
			if( hasfocus ) {
				style |= UI_PULSE;
			}
		}
		else {
			color = color_orange;
		}

		UI_DrawProportionalString( x, y, l->itemnames[i], style, color );
		y += PROP_HEIGHT;
	}
}