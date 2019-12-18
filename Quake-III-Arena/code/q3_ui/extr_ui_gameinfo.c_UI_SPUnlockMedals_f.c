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
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,char*) ; 
 int MAX_INFO_VALUE ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 int /*<<< orphan*/  trap_Print (char*) ; 

void UI_SPUnlockMedals_f( void ) {
	int		n;
	char	key[16];
	char	awardData[MAX_INFO_VALUE];

	trap_Cvar_VariableStringBuffer( "g_spAwards", awardData, MAX_INFO_VALUE );

	for( n = 0; n < 6; n++ ) {
		Com_sprintf( key, sizeof(key), "a%i", n );
		Info_SetValueForKey( awardData, key, "100" );
	}

	trap_Cvar_Set( "g_spAwards", awardData );

	trap_Print( "All levels unlocked at 100\n" );
}