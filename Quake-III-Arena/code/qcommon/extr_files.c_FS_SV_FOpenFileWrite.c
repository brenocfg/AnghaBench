#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t fileHandle_t ;
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_9__ {int /*<<< orphan*/  string; } ;
struct TYPE_6__ {int /*<<< orphan*/  o; } ;
struct TYPE_7__ {TYPE_1__ file; } ;
struct TYPE_8__ {TYPE_2__ handleFiles; void* handleSync; int /*<<< orphan*/  name; void* zipFile; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,char*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 char* FS_BuildOSPath (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ FS_CreatePath (char*) ; 
 size_t FS_HandleForFile () ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 TYPE_5__* fs_debug ; 
 TYPE_4__* fs_homepath ; 
 int /*<<< orphan*/  fs_searchpaths ; 
 TYPE_3__* fsh ; 
 void* qfalse ; 
 int strlen (char*) ; 

fileHandle_t FS_SV_FOpenFileWrite( const char *filename ) {
	char *ospath;
	fileHandle_t	f;

	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization\n" );
	}

	ospath = FS_BuildOSPath( fs_homepath->string, filename, "" );
	ospath[strlen(ospath)-1] = '\0';

	f = FS_HandleForFile();
	fsh[f].zipFile = qfalse;

	if ( fs_debug->integer ) {
		Com_Printf( "FS_SV_FOpenFileWrite: %s\n", ospath );
	}

	if( FS_CreatePath( ospath ) ) {
		return 0;
	}

	Com_DPrintf( "writing to: %s\n", ospath );
	fsh[f].handleFiles.file.o = fopen( ospath, "wb" );

	Q_strncpyz( fsh[f].name, filename, sizeof( fsh[f].name ) );

	fsh[f].handleSync = qfalse;
	if (!fsh[f].handleFiles.file.o) {
		f = 0;
	}
	return f;
}