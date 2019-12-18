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
struct TYPE_4__ {int /*<<< orphan*/  cursory; int /*<<< orphan*/  cursorx; } ;
struct TYPE_3__ {int /*<<< orphan*/  cursorY; int /*<<< orphan*/  cursorX; } ;

/* Variables and functions */
#define  CG_CONSOLE_COMMAND 136 
#define  CG_CROSSHAIR_PLAYER 135 
 int CG_ConsoleCommand () ; 
 int CG_CrosshairPlayer () ; 
#define  CG_DRAW_ACTIVE_FRAME 134 
 int /*<<< orphan*/  CG_DrawActiveFrame (int,int,int) ; 
#define  CG_EVENT_HANDLING 133 
 int /*<<< orphan*/  CG_Error (char*,int) ; 
 int /*<<< orphan*/  CG_EventHandling (int) ; 
#define  CG_INIT 132 
 int /*<<< orphan*/  CG_Init (int,int,int) ; 
#define  CG_KEY_EVENT 131 
 int /*<<< orphan*/  CG_KeyEvent (int,int) ; 
#define  CG_LAST_ATTACKER 130 
 int CG_LastAttacker () ; 
#define  CG_MOUSE_EVENT 129 
 int /*<<< orphan*/  CG_MouseEvent (int,int) ; 
#define  CG_SHUTDOWN 128 
 int /*<<< orphan*/  CG_Shutdown () ; 
 TYPE_2__ cgDC ; 
 TYPE_1__ cgs ; 

int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) {

	switch ( command ) {
	case CG_INIT:
		CG_Init( arg0, arg1, arg2 );
		return 0;
	case CG_SHUTDOWN:
		CG_Shutdown();
		return 0;
	case CG_CONSOLE_COMMAND:
		return CG_ConsoleCommand();
	case CG_DRAW_ACTIVE_FRAME:
		CG_DrawActiveFrame( arg0, arg1, arg2 );
		return 0;
	case CG_CROSSHAIR_PLAYER:
		return CG_CrosshairPlayer();
	case CG_LAST_ATTACKER:
		return CG_LastAttacker();
	case CG_KEY_EVENT:
		CG_KeyEvent(arg0, arg1);
		return 0;
	case CG_MOUSE_EVENT:
#ifdef MISSIONPACK
		cgDC.cursorx = cgs.cursorX;
		cgDC.cursory = cgs.cursorY;
#endif
		CG_MouseEvent(arg0, arg1);
		return 0;
	case CG_EVENT_HANDLING:
		CG_EventHandling(arg0);
		return 0;
	default:
		CG_Error( "vmMain: unknown command %i", command );
		break;
	}
	return -1;
}