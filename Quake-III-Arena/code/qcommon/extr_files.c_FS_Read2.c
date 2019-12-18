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
typedef  size_t fileHandle_t ;
struct TYPE_2__ {scalar_t__ streamed; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int FS_Read (void*,int,size_t) ; 
 int Sys_StreamedRead (void*,int,int,size_t) ; 
 int /*<<< orphan*/  fs_searchpaths ; 
 TYPE_1__* fsh ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

int FS_Read2( void *buffer, int len, fileHandle_t f ) {
	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization\n" );
	}

	if ( !f ) {
		return 0;
	}
	if (fsh[f].streamed) {
		int r;
		fsh[f].streamed = qfalse;
		r = Sys_StreamedRead( buffer, len, 1, f);
		fsh[f].streamed = qtrue;
		return r;
	} else {
		return FS_Read( buffer, len, f);
	}
}