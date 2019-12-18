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
struct TYPE_4__ {void* soundRegistered; void* rendererStarted; void* cgameStarted; void* uiStarted; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Shutdown ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ShutdownCGame () ; 
 int /*<<< orphan*/  CL_ShutdownUI () ; 
 int /*<<< orphan*/  S_DisableSounds () ; 
 TYPE_2__ cls ; 
 void* qfalse ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void CL_ShutdownAll(void) {

	// clear sounds
	S_DisableSounds();
	// shutdown CGame
	CL_ShutdownCGame();
	// shutdown UI
	CL_ShutdownUI();

	// shutdown the renderer
	if ( re.Shutdown ) {
		re.Shutdown( qfalse );		// don't destroy window or context
	}

	cls.uiStarted = qfalse;
	cls.cgameStarted = qfalse;
	cls.rendererStarted = qfalse;
	cls.soundRegistered = qfalse;
}