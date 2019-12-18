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
typedef  int /*<<< orphan*/  PARTITION ;
typedef  int /*<<< orphan*/  DIR_ENTRY ;

/* Variables and functions */
 int _FAT_directory_entryFromPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _FAT_partition_getPartitionFromPath (char const*) ; 
 char* strchr (char const*,char) ; 

bool _FAT_findEntry(const char *path, DIR_ENTRY *dirEntry) {
	PARTITION *partition = _FAT_partition_getPartitionFromPath(path);

	// Check Partition
	if( !partition )
		return false;

	// Move the path pointer to the start of the actual path
	if (strchr (path, ':') != NULL) {
		path = strchr (path, ':') + 1;
	}
	if (strchr (path, ':') != NULL) {
		return false;
	}

	// Search for the file on the disc
	return _FAT_directory_entryFromPath (partition, dirEntry, path, NULL);

}