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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  MOD_ALT ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegisterHotKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_SCREENSAVERRUNNING ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VK_TAB ; 
 scalar_t__ qtrue ; 
 scalar_t__ s_alttab_disabled ; 

__attribute__((used)) static void WIN_DisableAltTab( void )
{
	if ( s_alttab_disabled )
		return;

	if ( !Q_stricmp( Cvar_VariableString( "arch" ), "winnt" ) )
	{
		RegisterHotKey( 0, 0, MOD_ALT, VK_TAB );
	}
	else
	{
		BOOL old;

		SystemParametersInfo( SPI_SCREENSAVERRUNNING, 1, &old, 0 );
	}
	s_alttab_disabled = qtrue;
}