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
struct TYPE_2__ {char* question; int style; int slashX; int /*<<< orphan*/  (* draw ) () ;int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ART_CONFIRM_FRAME ; 
 int /*<<< orphan*/  Menu_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_DrawNamedPic (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int UI_INVERSE ; 
 int UI_LEFT ; 
 int /*<<< orphan*/  color_red ; 
 TYPE_1__ s_confirm ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void ConfirmMenu_Draw( void ) {
	UI_DrawNamedPic( 142, 118, 359, 256, ART_CONFIRM_FRAME );
	UI_DrawProportionalString( 320, 204, s_confirm.question, s_confirm.style, color_red );
	UI_DrawProportionalString( s_confirm.slashX, 265, "/", UI_LEFT|UI_INVERSE, color_red );

	Menu_Draw( &s_confirm.menu );

	if( s_confirm.draw ) {
		s_confirm.draw();
	}
}