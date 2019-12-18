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
typedef  int /*<<< orphan*/  videos ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_VALUE ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 int /*<<< orphan*/  va (char*,int) ; 

qboolean UI_ShowTierVideo( int tier ) {
	char	key[16];
	char	videos[MAX_INFO_VALUE];

	if( tier <= 0 ) {
		return qfalse;
	}

	trap_Cvar_VariableStringBuffer( "g_spVideos", videos, sizeof(videos) );

	Com_sprintf( key, sizeof(key), "tier%i", tier );
	if( atoi( Info_ValueForKey( videos, key ) ) ) {
		return qfalse;
	}

	Info_SetValueForKey( videos, key, va( "%i", 1 ) );
	trap_Cvar_Set( "g_spVideos", videos );

	return qtrue;
}