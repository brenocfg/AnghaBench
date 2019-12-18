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
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {int /*<<< orphan*/  (* Cmd_RemoveCommand ) (char*) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,scalar_t__) ;} ;
struct TYPE_3__ {scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLimp_Shutdown () ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  R_DeleteTextures () ; 
 int /*<<< orphan*/  R_DoneFreeType () ; 
 int /*<<< orphan*/  R_ShutdownCommandBuffers () ; 
 int /*<<< orphan*/  R_SyncRenderThread () ; 
 scalar_t__ qfalse ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub10 (char*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 
 int /*<<< orphan*/  stub3 (char*) ; 
 int /*<<< orphan*/  stub4 (char*) ; 
 int /*<<< orphan*/  stub5 (char*) ; 
 int /*<<< orphan*/  stub6 (char*) ; 
 int /*<<< orphan*/  stub7 (char*) ; 
 int /*<<< orphan*/  stub8 (char*) ; 
 int /*<<< orphan*/  stub9 (char*) ; 
 TYPE_1__ tr ; 

void RE_Shutdown( qboolean destroyWindow ) {	

	ri.Printf( PRINT_ALL, "RE_Shutdown( %i )\n", destroyWindow );

	ri.Cmd_RemoveCommand ("modellist");
	ri.Cmd_RemoveCommand ("screenshotJPEG");
	ri.Cmd_RemoveCommand ("screenshot");
	ri.Cmd_RemoveCommand ("imagelist");
	ri.Cmd_RemoveCommand ("shaderlist");
	ri.Cmd_RemoveCommand ("skinlist");
	ri.Cmd_RemoveCommand ("gfxinfo");
	ri.Cmd_RemoveCommand( "modelist" );
	ri.Cmd_RemoveCommand( "shaderstate" );


	if ( tr.registered ) {
		R_SyncRenderThread();
		R_ShutdownCommandBuffers();
		R_DeleteTextures();
	}

	R_DoneFreeType();

	// shut down platform specific OpenGL stuff
	if ( destroyWindow ) {
		GLimp_Shutdown();
	}

	tr.registered = qfalse;
}