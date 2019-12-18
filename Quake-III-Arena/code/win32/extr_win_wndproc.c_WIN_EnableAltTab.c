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
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SPI_SCREENSAVERRUNNING ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnregisterHotKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 scalar_t__ s_alttab_disabled ; 

__attribute__((used)) static void WIN_EnableAltTab( void )
{
	if ( s_alttab_disabled )
	{
		if ( !Q_stricmp( Cvar_VariableString( "arch" ), "winnt" ) )
		{
			UnregisterHotKey( 0, 0 );
		}
		else
		{
			BOOL old;

			SystemParametersInfo( SPI_SCREENSAVERRUNNING, 0, &old, 0 );
		}

		s_alttab_disabled = qfalse;
	}
}