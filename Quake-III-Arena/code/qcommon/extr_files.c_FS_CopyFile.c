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
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 scalar_t__ FS_CreatePath (char*) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static void FS_CopyFile( char *fromOSPath, char *toOSPath ) {
	FILE	*f;
	int		len;
	byte	*buf;

	Com_Printf( "copy %s to %s\n", fromOSPath, toOSPath );

	if (strstr(fromOSPath, "journal.dat") || strstr(fromOSPath, "journaldata.dat")) {
		Com_Printf( "Ignoring journal files\n");
		return;
	}

	f = fopen( fromOSPath, "rb" );
	if ( !f ) {
		return;
	}
	fseek (f, 0, SEEK_END);
	len = ftell (f);
	fseek (f, 0, SEEK_SET);

	// we are using direct malloc instead of Z_Malloc here, so it
	// probably won't work on a mac... Its only for developers anyway...
	buf = malloc( len );
	if (fread( buf, 1, len, f ) != len)
		Com_Error( ERR_FATAL, "Short read in FS_Copyfiles()\n" );
	fclose( f );

	if( FS_CreatePath( toOSPath ) ) {
		return;
	}

	f = fopen( toOSPath, "wb" );
	if ( !f ) {
		return;
	}
	if (fwrite( buf, 1, len, f ) != len)
		Com_Error( ERR_FATAL, "Short write in FS_Copyfiles()\n" );
	fclose( f );
	free( buf );
}