#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dwPlatformId; int dwMajorVersion; } ;
struct TYPE_8__ {int /*<<< orphan*/  hWnd; TYPE_1__ osversion; } ;
struct TYPE_7__ {int integer; } ;
struct TYPE_6__ {void* mouseInitialized; void* mouseStartupDelayed; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 scalar_t__ IN_InitDIMouse () ; 
 int /*<<< orphan*/  IN_InitWin32Mouse () ; 
 scalar_t__ VER_PLATFORM_WIN32_NT ; 
 TYPE_4__ g_wv ; 
 TYPE_3__* in_mouse ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_2__ s_wmv ; 

void IN_StartupMouse( void ) 
{
	s_wmv.mouseInitialized = qfalse;
  s_wmv.mouseStartupDelayed = qfalse;

	if ( in_mouse->integer == 0 ) {
		Com_Printf ("Mouse control not active.\n");
		return;
	}

	// nt4.0 direct input is screwed up
	if ( ( g_wv.osversion.dwPlatformId == VER_PLATFORM_WIN32_NT ) &&
		 ( g_wv.osversion.dwMajorVersion == 4 ) )
	{
		Com_Printf ("Disallowing DirectInput on NT 4.0\n");
		Cvar_Set( "in_mouse", "-1" );
	}

	if ( in_mouse->integer == -1 ) {
		Com_Printf ("Skipping check for DirectInput\n");
	} else {
    if (!g_wv.hWnd)
    {
      Com_Printf ("No window for DirectInput mouse init, delaying\n");
      s_wmv.mouseStartupDelayed = qtrue;
      return;
    }
		if ( IN_InitDIMouse() ) {
	    s_wmv.mouseInitialized = qtrue;
			return;
		}
		Com_Printf ("Falling back to Win32 mouse support...\n");
	}
	s_wmv.mouseInitialized = qtrue;
	IN_InitWin32Mouse();
}