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
struct TYPE_2__ {int /*<<< orphan*/  (* draw ) () ;int /*<<< orphan*/  menu; int /*<<< orphan*/  style; scalar_t__* lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  ART_CONFIRM_FRAME ; 
 int /*<<< orphan*/  Menu_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_DrawNamedPic (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_red ; 
 TYPE_1__ s_confirm ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void MessageMenu_Draw( void ) {
	int i,y;
	
	UI_DrawNamedPic( 142, 118, 359, 256, ART_CONFIRM_FRAME );
	
	y = 188;
	for(i=0; s_confirm.lines[i]; i++)
	{
		UI_DrawProportionalString( 320, y, s_confirm.lines[i], s_confirm.style, color_red );
		y += 18;
	}

	Menu_Draw( &s_confirm.menu );

	if( s_confirm.draw ) {
		s_confirm.draw();
	}
}