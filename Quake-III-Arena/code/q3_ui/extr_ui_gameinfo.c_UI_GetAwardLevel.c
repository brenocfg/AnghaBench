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
typedef  int /*<<< orphan*/  awardData ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_VALUE ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 

int UI_GetAwardLevel( int award ) {
	char	key[16];
	char	awardData[MAX_INFO_VALUE];

	trap_Cvar_VariableStringBuffer( "g_spAwards", awardData, sizeof(awardData) );

	Com_sprintf( key, sizeof(key), "a%i", award );
	return atoi( Info_ValueForKey( awardData, key ) );
}