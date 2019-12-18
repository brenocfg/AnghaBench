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

/* Variables and functions */
 int /*<<< orphan*/  IN_DIMouse (int*,int*) ; 
 int /*<<< orphan*/  IN_Win32Mouse (int*,int*) ; 
 int /*<<< orphan*/  SE_MOUSE ; 
 int /*<<< orphan*/  Sys_QueEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ g_pMouse ; 

void IN_MouseMove ( void ) {
	int		mx, my;

	if ( g_pMouse ) {
		IN_DIMouse( &mx, &my );
	} else {
		IN_Win32Mouse( &mx, &my );
	}

	if ( !mx && !my ) {
		return;
	}

	Sys_QueEvent( 0, SE_MOUSE, mx, my, 0, NULL );
}