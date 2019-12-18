#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  len ;
typedef  scalar_t__ fileHandle_t ;
typedef  int byte ;
struct TYPE_2__ {int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,char const*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 int FS_FOpenFileRead (char const*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  FS_Flush (scalar_t__) ; 
 int FS_Read (int*,int,scalar_t__) ; 
 int /*<<< orphan*/  FS_Write (int*,int,scalar_t__) ; 
 int* Hunk_AllocateTempMemory (int) ; 
 TYPE_1__* com_journal ; 
 scalar_t__ com_journalDataFile ; 
 int /*<<< orphan*/  fs_loadCount ; 
 int /*<<< orphan*/  fs_loadStack ; 
 int /*<<< orphan*/  fs_searchpaths ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 scalar_t__ strstr (char const*,char*) ; 

int FS_ReadFile( const char *qpath, void **buffer ) {
	fileHandle_t	h;
	byte*			buf;
	qboolean		isConfig;
	int				len;

	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization\n" );
	}

	if ( !qpath || !qpath[0] ) {
		Com_Error( ERR_FATAL, "FS_ReadFile with empty name\n" );
	}

	buf = NULL;	// quiet compiler warning

	// if this is a .cfg file and we are playing back a journal, read
	// it from the journal file
	if ( strstr( qpath, ".cfg" ) ) {
		isConfig = qtrue;
		if ( com_journal && com_journal->integer == 2 ) {
			int		r;

			Com_DPrintf( "Loading %s from journal file.\n", qpath );
			r = FS_Read( &len, sizeof( len ), com_journalDataFile );
			if ( r != sizeof( len ) ) {
				if (buffer != NULL) *buffer = NULL;
				return -1;
			}
			// if the file didn't exist when the journal was created
			if (!len) {
				if (buffer == NULL) {
					return 1;			// hack for old journal files
				}
				*buffer = NULL;
				return -1;
			}
			if (buffer == NULL) {
				return len;
			}

			buf = Hunk_AllocateTempMemory(len+1);
			*buffer = buf;

			r = FS_Read( buf, len, com_journalDataFile );
			if ( r != len ) {
				Com_Error( ERR_FATAL, "Read from journalDataFile failed" );
			}

			fs_loadCount++;
			fs_loadStack++;

			// guarantee that it will have a trailing 0 for string operations
			buf[len] = 0;

			return len;
		}
	} else {
		isConfig = qfalse;
	}

	// look for it in the filesystem or pack files
	len = FS_FOpenFileRead( qpath, &h, qfalse );
	if ( h == 0 ) {
		if ( buffer ) {
			*buffer = NULL;
		}
		// if we are journalling and it is a config file, write a zero to the journal file
		if ( isConfig && com_journal && com_journal->integer == 1 ) {
			Com_DPrintf( "Writing zero for %s to journal file.\n", qpath );
			len = 0;
			FS_Write( &len, sizeof( len ), com_journalDataFile );
			FS_Flush( com_journalDataFile );
		}
		return -1;
	}
	
	if ( !buffer ) {
		if ( isConfig && com_journal && com_journal->integer == 1 ) {
			Com_DPrintf( "Writing len for %s to journal file.\n", qpath );
			FS_Write( &len, sizeof( len ), com_journalDataFile );
			FS_Flush( com_journalDataFile );
		}
		FS_FCloseFile( h);
		return len;
	}

	fs_loadCount++;
	fs_loadStack++;

	buf = Hunk_AllocateTempMemory(len+1);
	*buffer = buf;

	FS_Read (buf, len, h);

	// guarantee that it will have a trailing 0 for string operations
	buf[len] = 0;
	FS_FCloseFile( h );

	// if we are journalling and it is a config file, write it to the journal file
	if ( isConfig && com_journal && com_journal->integer == 1 ) {
		Com_DPrintf( "Writing %s to journal file.\n", qpath );
		FS_Write( &len, sizeof( len ), com_journalDataFile );
		FS_Write( buf, len, com_journalDataFile );
		FS_Flush( com_journalDataFile );
	}
	return len;
}