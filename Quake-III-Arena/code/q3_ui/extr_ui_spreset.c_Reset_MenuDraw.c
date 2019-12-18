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
struct TYPE_2__ {int slashX; int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ART_FRAME ; 
 int /*<<< orphan*/  Menu_Draw (int /*<<< orphan*/ *) ; 
 int PROP_HEIGHT ; 
 int SCREEN_WIDTH ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawNamedPic (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int UI_INVERSE ; 
 int UI_LEFT ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  color_red ; 
 int /*<<< orphan*/  color_yellow ; 
 TYPE_1__ s_reset ; 

__attribute__((used)) static void Reset_MenuDraw( void ) {
	UI_DrawNamedPic( 142, 118, 359, 256, ART_FRAME );
	UI_DrawProportionalString( 320, 194 + 10, "RESET GAME?", UI_CENTER|UI_INVERSE, color_red );
	UI_DrawProportionalString( s_reset.slashX, 265, "/", UI_LEFT|UI_INVERSE, color_red );
	Menu_Draw( &s_reset.menu );

	UI_DrawProportionalString( SCREEN_WIDTH/2, 356 + PROP_HEIGHT * 0, "WARNING: This resets all of the", UI_CENTER|UI_SMALLFONT, color_yellow );
	UI_DrawProportionalString( SCREEN_WIDTH/2, 356 + PROP_HEIGHT * 1, "single player game variables.", UI_CENTER|UI_SMALLFONT, color_yellow );
	UI_DrawProportionalString( SCREEN_WIDTH/2, 356 + PROP_HEIGHT * 2, "Do this only if you want to", UI_CENTER|UI_SMALLFONT, color_yellow );
	UI_DrawProportionalString( SCREEN_WIDTH/2, 356 + PROP_HEIGHT * 3, "start over from the beginning.", UI_CENTER|UI_SMALLFONT, color_yellow );
}