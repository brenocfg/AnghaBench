#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* pack; struct TYPE_6__* next; } ;
typedef  TYPE_1__ searchpath_t ;
struct TYPE_7__ {int pure_checksum; TYPE_3__** hashTable; int /*<<< orphan*/  hashSize; } ;
typedef  TYPE_2__ pack_t ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ fileInPack_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  FS_FilenameCompare (int /*<<< orphan*/ ,char const*) ; 
 long FS_HashFileName (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_PakIsPure (TYPE_2__*) ; 
 TYPE_1__* fs_searchpaths ; 
 scalar_t__ strstr (char const*,char*) ; 

int	FS_FileIsInPAK(const char *filename, int *pChecksum ) {
	searchpath_t	*search;
	pack_t			*pak;
	fileInPack_t	*pakFile;
	long			hash = 0;

	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization\n" );
	}

	if ( !filename ) {
		Com_Error( ERR_FATAL, "FS_FOpenFileRead: NULL 'filename' parameter passed\n" );
	}

	// qpaths are not supposed to have a leading slash
	if ( filename[0] == '/' || filename[0] == '\\' ) {
		filename++;
	}

	// make absolutely sure that it can't back up the path.
	// The searchpaths do guarantee that something will always
	// be prepended, so we don't need to worry about "c:" or "//limbo" 
	if ( strstr( filename, ".." ) || strstr( filename, "::" ) ) {
		return -1;
	}

	//
	// search through the path, one element at a time
	//

	for ( search = fs_searchpaths ; search ; search = search->next ) {
		//
		if (search->pack) {
			hash = FS_HashFileName(filename, search->pack->hashSize);
		}
		// is the element a pak file?
		if ( search->pack && search->pack->hashTable[hash] ) {
			// disregard if it doesn't match one of the allowed pure pak files
			if ( !FS_PakIsPure(search->pack) ) {
				continue;
			}

			// look through all the pak file elements
			pak = search->pack;
			pakFile = pak->hashTable[hash];
			do {
				// case and separator insensitive comparisons
				if ( !FS_FilenameCompare( pakFile->name, filename ) ) {
					if (pChecksum) {
						*pChecksum = pak->pure_checksum;
					}
					return 1;
				}
				pakFile = pakFile->next;
			} while(pakFile != NULL);
		}
	}
	return -1;
}