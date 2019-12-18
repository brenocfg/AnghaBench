#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {char const* filename; int /*<<< orphan*/  entryData; } ;
typedef  int /*<<< orphan*/  PARTITION ;
typedef  TYPE_1__ DIR_ENTRY ;

/* Variables and functions */
 int MAX_ALIAS_LENGTH ; 
 size_t NAME_MAX ; 
 int /*<<< orphan*/  _FAT_directory_entryGetAlias (int /*<<< orphan*/ ,char*) ; 
 int _FAT_directory_getFirstEntry (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _FAT_directory_getNextEntry (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ _FAT_directory_mbsncasecmp (char const*,char const*,size_t) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 size_t strnlen (char const*,size_t) ; 

__attribute__((used)) static bool _FAT_directory_entryExists (PARTITION* partition, const char* name, uint32_t dirCluster) {
	DIR_ENTRY tempEntry;
	bool foundFile;
	char alias[MAX_ALIAS_LENGTH];
	size_t dirnameLength;

	dirnameLength = strnlen(name, NAME_MAX);

	if (dirnameLength >= NAME_MAX) {
		return false;
	}

	// Make sure the entry doesn't already exist
	foundFile = _FAT_directory_getFirstEntry (partition, &tempEntry, dirCluster);

	while (foundFile) {			// It hasn't already found the file
		// Check if the filename matches
		if ((dirnameLength == strnlen(tempEntry.filename, NAME_MAX))
			&& (_FAT_directory_mbsncasecmp(name, tempEntry.filename, dirnameLength) == 0)) {
				return true;
		}

		// Check if the alias matches
		_FAT_directory_entryGetAlias (tempEntry.entryData, alias);
		if ((strncasecmp(name, alias, MAX_ALIAS_LENGTH) == 0)) {
				return true;
		}
		foundFile = _FAT_directory_getNextEntry (partition, &tempEntry);
	}
	return false;
}