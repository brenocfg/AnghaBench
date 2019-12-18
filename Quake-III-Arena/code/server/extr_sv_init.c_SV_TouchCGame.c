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
typedef  int /*<<< orphan*/  filename ;
typedef  scalar_t__ fileHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 int /*<<< orphan*/  FS_FOpenFileRead (char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  qfalse ; 

void SV_TouchCGame(void) {
	fileHandle_t	f;
	char filename[MAX_QPATH];

	Com_sprintf( filename, sizeof(filename), "vm/%s.qvm", "cgame" );
	FS_FOpenFileRead( filename, &f, qfalse );
	if ( f ) {
		FS_FCloseFile( f );
	}
}