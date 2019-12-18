#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* string; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_INIT ; 
 int CVAR_SYSTEMINFO ; 
 int /*<<< orphan*/  Com_WriteCDKey (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Com_WriteConfigToFile (char*) ; 
 TYPE_1__* Cvar_Get (char*,char*,int) ; 
 scalar_t__ UI_usesUniqueCDKey () ; 
 int /*<<< orphan*/ * cl_cdkey ; 
 int /*<<< orphan*/  com_fullyInitialized ; 
 int cvar_modifiedFlags ; 

void Com_WriteConfiguration( void ) {
#ifndef DEDICATED // bk001204
	cvar_t	*fs;
#endif
	// if we are quiting without fully initializing, make sure
	// we don't write out anything
	if ( !com_fullyInitialized ) {
		return;
	}

	if ( !(cvar_modifiedFlags & CVAR_ARCHIVE ) ) {
		return;
	}
	cvar_modifiedFlags &= ~CVAR_ARCHIVE;

	Com_WriteConfigToFile( "q3config.cfg" );

	// bk001119 - tentative "not needed for dedicated"
#ifndef DEDICATED
	fs = Cvar_Get ("fs_game", "", CVAR_INIT|CVAR_SYSTEMINFO );
	if (UI_usesUniqueCDKey() && fs && fs->string[0] != 0) {
		Com_WriteCDKey( fs->string, &cl_cdkey[16] );
	} else {
		Com_WriteCDKey( "baseq3", cl_cdkey );
	}
#endif
}