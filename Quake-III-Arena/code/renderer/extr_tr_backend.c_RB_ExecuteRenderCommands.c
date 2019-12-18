#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int msec; } ;
struct TYPE_12__ {int smpFrame; TYPE_2__ pc; } ;
struct TYPE_7__ {void const* cmds; } ;
struct TYPE_11__ {TYPE_1__ commands; } ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;
struct TYPE_9__ {int (* Milliseconds ) () ;} ;

/* Variables and functions */
 void* RB_DrawBuffer (void const*) ; 
 void* RB_DrawSurfs (void const*) ; 
 void* RB_SetColor (void const*) ; 
 void* RB_StretchPic (void const*) ; 
 void* RB_SwapBuffers (void const*) ; 
 void* RB_TakeScreenshotCmd (void const*) ; 
#define  RC_DRAW_BUFFER 134 
#define  RC_DRAW_SURFS 133 
#define  RC_END_OF_LIST 132 
#define  RC_SCREENSHOT 131 
#define  RC_SET_COLOR 130 
#define  RC_STRETCH_PIC 129 
#define  RC_SWAP_BUFFERS 128 
 TYPE_6__ backEnd ; 
 TYPE_5__** backEndData ; 
 TYPE_4__* r_smp ; 
 TYPE_3__ ri ; 
 int stub1 () ; 
 int stub2 () ; 

void RB_ExecuteRenderCommands( const void *data ) {
	int		t1, t2;

	t1 = ri.Milliseconds ();

	if ( !r_smp->integer || data == backEndData[0]->commands.cmds ) {
		backEnd.smpFrame = 0;
	} else {
		backEnd.smpFrame = 1;
	}

	while ( 1 ) {
		switch ( *(const int *)data ) {
		case RC_SET_COLOR:
			data = RB_SetColor( data );
			break;
		case RC_STRETCH_PIC:
			data = RB_StretchPic( data );
			break;
		case RC_DRAW_SURFS:
			data = RB_DrawSurfs( data );
			break;
		case RC_DRAW_BUFFER:
			data = RB_DrawBuffer( data );
			break;
		case RC_SWAP_BUFFERS:
			data = RB_SwapBuffers( data );
			break;
		case RC_SCREENSHOT:
			data = RB_TakeScreenshotCmd( data );
			break;

		case RC_END_OF_LIST:
		default:
			// stop rendering on this thread
			t2 = ri.Milliseconds ();
			backEnd.pc.msec = t2 - t1;
			return;
		}
	}

}