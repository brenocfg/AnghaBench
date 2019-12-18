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
struct TYPE_2__ {int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ART_BACKGROUND ; 
 int /*<<< orphan*/  Menu_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawBannerString (int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawNamedPic (int,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ addBotsMenuInfo ; 
 int /*<<< orphan*/  color_white ; 

__attribute__((used)) static void UI_AddBotsMenu_Draw( void ) {
	UI_DrawBannerString( 320, 16, "ADD BOTS", UI_CENTER, color_white );
	UI_DrawNamedPic( 320-233, 240-166, 466, 332, ART_BACKGROUND );

	// standard menu drawing
	Menu_Draw( &addBotsMenuInfo.menu );
}