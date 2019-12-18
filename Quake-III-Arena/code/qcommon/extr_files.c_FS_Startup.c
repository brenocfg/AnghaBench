#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* string; } ;
typedef  TYPE_1__ cvar_t ;
struct TYPE_12__ {char const* string; } ;
struct TYPE_11__ {char* string; } ;
struct TYPE_10__ {char* string; } ;
struct TYPE_9__ {char const* string; int /*<<< orphan*/  modified; } ;
struct TYPE_8__ {char const* string; } ;

/* Variables and functions */
 char const* BASEGAME ; 
 int CVAR_INIT ; 
 int CVAR_SYSTEMINFO ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  Com_AppendCDKey (scalar_t__*) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  Com_ReadCDKey (char*) ; 
 void* Cvar_Get (char*,char const*,int) ; 
 int /*<<< orphan*/  FS_AddGameDirectory (char*,char const*) ; 
 int /*<<< orphan*/  FS_Dir_f () ; 
 int /*<<< orphan*/  FS_NewDir_f () ; 
 int /*<<< orphan*/  FS_Path_f () ; 
 int /*<<< orphan*/  FS_ReorderPurePaks () ; 
 int /*<<< orphan*/  FS_TouchFile_f () ; 
 scalar_t__ Q_stricmp (char const*,char const*) ; 
 char* Sys_DefaultCDPath () ; 
 char* Sys_DefaultHomePath () ; 
 char* Sys_DefaultInstallPath () ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 TYPE_6__* fs_basegame ; 
 TYPE_5__* fs_basepath ; 
 TYPE_4__* fs_cdpath ; 
 void* fs_copyfiles ; 
 void* fs_debug ; 
 TYPE_3__* fs_gamedirvar ; 
 TYPE_2__* fs_homepath ; 
 int /*<<< orphan*/  fs_packFiles ; 
 void* fs_restrict ; 
 int /*<<< orphan*/ * missingFiles ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void FS_Startup( const char *gameName ) {
        const char *homePath;
	cvar_t	*fs;

	Com_Printf( "----- FS_Startup -----\n" );

	fs_debug = Cvar_Get( "fs_debug", "0", 0 );
	fs_copyfiles = Cvar_Get( "fs_copyfiles", "0", CVAR_INIT );
	fs_cdpath = Cvar_Get ("fs_cdpath", Sys_DefaultCDPath(), CVAR_INIT );
	fs_basepath = Cvar_Get ("fs_basepath", Sys_DefaultInstallPath(), CVAR_INIT );
	fs_basegame = Cvar_Get ("fs_basegame", "", CVAR_INIT );
  homePath = Sys_DefaultHomePath();
  if (!homePath || !homePath[0]) {
		homePath = fs_basepath->string;
	}
	fs_homepath = Cvar_Get ("fs_homepath", homePath, CVAR_INIT );
	fs_gamedirvar = Cvar_Get ("fs_game", "", CVAR_INIT|CVAR_SYSTEMINFO );
	fs_restrict = Cvar_Get ("fs_restrict", "", CVAR_INIT );

	// add search path elements in reverse priority order
	if (fs_cdpath->string[0]) {
		FS_AddGameDirectory( fs_cdpath->string, gameName );
	}
	if (fs_basepath->string[0]) {
		FS_AddGameDirectory( fs_basepath->string, gameName );
	}
  // fs_homepath is somewhat particular to *nix systems, only add if relevant
  // NOTE: same filtering below for mods and basegame
	if (fs_basepath->string[0] && Q_stricmp(fs_homepath->string,fs_basepath->string)) {
		FS_AddGameDirectory ( fs_homepath->string, gameName );
	}
        
	// check for additional base game so mods can be based upon other mods
	if ( fs_basegame->string[0] && !Q_stricmp( gameName, BASEGAME ) && Q_stricmp( fs_basegame->string, gameName ) ) {
		if (fs_cdpath->string[0]) {
			FS_AddGameDirectory(fs_cdpath->string, fs_basegame->string);
		}
		if (fs_basepath->string[0]) {
			FS_AddGameDirectory(fs_basepath->string, fs_basegame->string);
		}
		if (fs_homepath->string[0] && Q_stricmp(fs_homepath->string,fs_basepath->string)) {
			FS_AddGameDirectory(fs_homepath->string, fs_basegame->string);
		}
	}

	// check for additional game folder for mods
	if ( fs_gamedirvar->string[0] && !Q_stricmp( gameName, BASEGAME ) && Q_stricmp( fs_gamedirvar->string, gameName ) ) {
		if (fs_cdpath->string[0]) {
			FS_AddGameDirectory(fs_cdpath->string, fs_gamedirvar->string);
		}
		if (fs_basepath->string[0]) {
			FS_AddGameDirectory(fs_basepath->string, fs_gamedirvar->string);
		}
		if (fs_homepath->string[0] && Q_stricmp(fs_homepath->string,fs_basepath->string)) {
			FS_AddGameDirectory(fs_homepath->string, fs_gamedirvar->string);
		}
	}

	Com_ReadCDKey( "baseq3" );
	fs = Cvar_Get ("fs_game", "", CVAR_INIT|CVAR_SYSTEMINFO );
	if (fs && fs->string[0] != 0) {
		Com_AppendCDKey( fs->string );
	}

	// add our commands
	Cmd_AddCommand ("path", FS_Path_f);
	Cmd_AddCommand ("dir", FS_Dir_f );
	Cmd_AddCommand ("fdir", FS_NewDir_f );
	Cmd_AddCommand ("touchFile", FS_TouchFile_f );

	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=506
	// reorder the pure pk3 files according to server order
	FS_ReorderPurePaks();
	
	// print the current search paths
	FS_Path_f();

	fs_gamedirvar->modified = qfalse; // We just loaded, it's not modified

	Com_Printf( "----------------------\n" );

#ifdef FS_MISSING
	if (missingFiles == NULL) {
		missingFiles = fopen( "\\missing.txt", "ab" );
	}
#endif
	Com_Printf( "%d files in pk3 files\n", fs_packFiles );
}