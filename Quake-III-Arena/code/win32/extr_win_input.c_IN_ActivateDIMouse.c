#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectInputDevice_Acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_InitDIMouse () ; 
 int /*<<< orphan*/  g_pMouse ; 

void IN_ActivateDIMouse( void ) {
	HRESULT		hr;

	if (!g_pMouse) {
		return;
	}

	// we may fail to reacquire if the window has been recreated
	hr = IDirectInputDevice_Acquire( g_pMouse );
	if (FAILED(hr)) {
		if ( !IN_InitDIMouse() ) {
			Com_Printf ("Falling back to Win32 mouse support...\n");
			Cvar_Set( "in_mouse", "-1" );
		}
	}
}