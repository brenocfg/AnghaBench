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
struct TYPE_4__ {scalar_t__ integer; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 char* FS_BuildOSPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  FS_CopyFile (char*,char*) ; 
 int /*<<< orphan*/  FS_Remove (char*) ; 
 int /*<<< orphan*/  S_ClearSoundBuffer () ; 
 TYPE_2__* fs_debug ; 
 int /*<<< orphan*/  fs_gamedir ; 
 TYPE_1__* fs_homepath ; 
 int /*<<< orphan*/  fs_searchpaths ; 
 scalar_t__ rename (char*,char*) ; 

void FS_Rename( const char *from, const char *to ) {
	char			*from_ospath, *to_ospath;

	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization\n" );
	}

	// don't let sound stutter
	S_ClearSoundBuffer();

	from_ospath = FS_BuildOSPath( fs_homepath->string, fs_gamedir, from );
	to_ospath = FS_BuildOSPath( fs_homepath->string, fs_gamedir, to );

	if ( fs_debug->integer ) {
		Com_Printf( "FS_Rename: %s --> %s\n", from_ospath, to_ospath );
	}

	if (rename( from_ospath, to_ospath )) {
		// Failed, try copying it and deleting the original
		FS_CopyFile ( from_ospath, to_ospath );
		FS_Remove ( from_ospath );
	}
}