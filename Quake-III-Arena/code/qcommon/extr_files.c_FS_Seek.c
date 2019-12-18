#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t fileHandle_t ;
struct TYPE_4__ {int /*<<< orphan*/  z; } ;
struct TYPE_5__ {TYPE_1__ file; } ;
struct TYPE_6__ {scalar_t__ zipFile; TYPE_2__ handleFiles; int /*<<< orphan*/  zipFilePos; scalar_t__ streamed; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/ * FS_FileForHandle (size_t) ; 
 int FS_Read (char*,long,size_t) ; 
#define  FS_SEEK_CUR 130 
#define  FS_SEEK_END 129 
#define  FS_SEEK_SET 128 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 int /*<<< orphan*/  Sys_StreamSeek (size_t,long,int) ; 
 int /*<<< orphan*/  fs_searchpaths ; 
 int fseek (int /*<<< orphan*/ *,long,int) ; 
 TYPE_3__* fsh ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int unzOpenCurrentFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unzSetCurrentFileInfoPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int FS_Seek( fileHandle_t f, long offset, int origin ) {
	int		_origin;
	char	foo[65536];

	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization\n" );
		return -1;
	}

	if (fsh[f].streamed) {
		fsh[f].streamed = qfalse;
		Sys_StreamSeek( f, offset, origin );
		fsh[f].streamed = qtrue;
	}

	if (fsh[f].zipFile == qtrue) {
		if (offset == 0 && origin == FS_SEEK_SET) {
			// set the file position in the zip file (also sets the current file info)
			unzSetCurrentFileInfoPosition(fsh[f].handleFiles.file.z, fsh[f].zipFilePos);
			return unzOpenCurrentFile(fsh[f].handleFiles.file.z);
		} else if (offset<65536) {
			// set the file position in the zip file (also sets the current file info)
			unzSetCurrentFileInfoPosition(fsh[f].handleFiles.file.z, fsh[f].zipFilePos);
			unzOpenCurrentFile(fsh[f].handleFiles.file.z);
			return FS_Read(foo, offset, f);
		} else {
			Com_Error( ERR_FATAL, "ZIP FILE FSEEK NOT YET IMPLEMENTED\n" );
			return -1;
		}
	} else {
		FILE *file;
		file = FS_FileForHandle(f);
		switch( origin ) {
		case FS_SEEK_CUR:
			_origin = SEEK_CUR;
			break;
		case FS_SEEK_END:
			_origin = SEEK_END;
			break;
		case FS_SEEK_SET:
			_origin = SEEK_SET;
			break;
		default:
			_origin = SEEK_CUR;
			Com_Error( ERR_FATAL, "Bad origin in FS_Seek\n" );
			break;
		}

		return fseek( file, offset, _origin );
	}
}