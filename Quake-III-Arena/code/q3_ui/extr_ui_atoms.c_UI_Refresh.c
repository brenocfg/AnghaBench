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
struct TYPE_4__ {int /*<<< orphan*/  (* draw ) () ;scalar_t__ showlogo; scalar_t__ fullscreen; } ;
struct TYPE_3__ {int frametime; int realtime; scalar_t__ cursory; scalar_t__ cursorx; scalar_t__ debug; int /*<<< orphan*/  cursor; void* firstdraw; TYPE_2__* activemenu; int /*<<< orphan*/  menuBackNoLogoShader; int /*<<< orphan*/  menuBackShader; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_LOCAL_SOUND ; 
 int KEYCATCH_UI ; 
 int /*<<< orphan*/  Menu_Draw (TYPE_2__*) ; 
 int SCREEN_HEIGHT ; 
 int SCREEN_WIDTH ; 
 int /*<<< orphan*/  UI_DrawHandlePic (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int UI_LEFT ; 
 int /*<<< orphan*/  UI_MouseEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  UI_SetColor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_UpdateCvars () ; 
 int /*<<< orphan*/  colorRed ; 
 void* m_entersound ; 
 int /*<<< orphan*/  menu_in_sound ; 
 void* qfalse ; 
 int /*<<< orphan*/  stub1 () ; 
 int trap_Key_GetCatcher () ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ uis ; 
 int /*<<< orphan*/  va (char*,scalar_t__,scalar_t__) ; 

void UI_Refresh( int realtime )
{
	uis.frametime = realtime - uis.realtime;
	uis.realtime  = realtime;

	if ( !( trap_Key_GetCatcher() & KEYCATCH_UI ) ) {
		return;
	}

	UI_UpdateCvars();

	if ( uis.activemenu )
	{
		if (uis.activemenu->fullscreen)
		{
			// draw the background
			if( uis.activemenu->showlogo ) {
				UI_DrawHandlePic( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, uis.menuBackShader );
			}
			else {
				UI_DrawHandlePic( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, uis.menuBackNoLogoShader );
			}
		}

		if (uis.activemenu->draw)
			uis.activemenu->draw();
		else
			Menu_Draw( uis.activemenu );

		if( uis.firstdraw ) {
			UI_MouseEvent( 0, 0 );
			uis.firstdraw = qfalse;
		}
	}

	// draw cursor
	UI_SetColor( NULL );
	UI_DrawHandlePic( uis.cursorx-16, uis.cursory-16, 32, 32, uis.cursor);

#ifndef NDEBUG
	if (uis.debug)
	{
		// cursor coordinates
		UI_DrawString( 0, 0, va("(%d,%d)",uis.cursorx,uis.cursory), UI_LEFT|UI_SMALLFONT, colorRed );
	}
#endif

	// delay playing the enter sound until after the
	// menu has been drawn, to avoid delay while
	// caching images
	if (m_entersound)
	{
		trap_S_StartLocalSound( menu_in_sound, CHAN_LOCAL_SOUND );
		m_entersound = qfalse;
	}
}