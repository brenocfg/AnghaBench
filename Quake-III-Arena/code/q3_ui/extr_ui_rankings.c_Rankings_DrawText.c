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
typedef  int qboolean ;
struct TYPE_7__ {char* buffer; int cursor; } ;
struct TYPE_6__ {int x; int y; scalar_t__ menuPosition; TYPE_1__* parent; } ;
struct TYPE_8__ {TYPE_3__ field; TYPE_2__ generic; } ;
typedef  TYPE_4__ menufield_s ;
struct TYPE_5__ {scalar_t__ cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_WHITE ; 
 size_t ColorIndex (int /*<<< orphan*/ ) ; 
 int SMALLCHAR_WIDTH ; 
 int UI_BLINK ; 
 int /*<<< orphan*/  UI_DrawChar (int,int,char,int,float*) ; 
 int UI_LEFT ; 
 int UI_PULSE ; 
 int UI_SMALLFONT ; 
 float* color_white ; 
 float** g_color_table ; 
 float* text_color_highlight ; 
 float* text_color_normal ; 
 scalar_t__ trap_Key_GetOverstrikeMode () ; 

void Rankings_DrawText( void* self )
{
	menufield_s		*f;
	qboolean		focus;
	int				style;
	char			*txt;
	char			c;
	float			*color;
	int				basex, x, y;

	f = (menufield_s*)self;
	basex = f->generic.x;
	y = f->generic.y + 4;
	focus = (f->generic.parent->cursor == f->generic.menuPosition);

	style = UI_LEFT|UI_SMALLFONT;
	color = text_color_normal;
	if( focus ) {
		style |= UI_PULSE;
		color = text_color_highlight;
	}

	// draw the actual text
	txt = f->field.buffer;
	color = g_color_table[ColorIndex(COLOR_WHITE)];
	x = basex;
	while ( (c = *txt) != 0 ) {
		UI_DrawChar( x, y, c, style, color );
		txt++;
		x += SMALLCHAR_WIDTH;
	}

	// draw cursor if we have focus
	if( focus ) {
		if ( trap_Key_GetOverstrikeMode() ) {
			c = 11;
		} else {
			c = 10;
		}

		style &= ~UI_PULSE;
		style |= UI_BLINK;

		UI_DrawChar( basex + f->field.cursor * SMALLCHAR_WIDTH, y, c, style, color_white );
	}
}