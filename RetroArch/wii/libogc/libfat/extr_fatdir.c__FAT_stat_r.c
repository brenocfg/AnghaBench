#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct _reent {int /*<<< orphan*/  _errno; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ PARTITION ;
typedef  int /*<<< orphan*/  DIR_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  _FAT_directory_entryFromPath (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_directory_entryStat (TYPE_1__*,int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__* _FAT_partition_getPartitionFromPath (char const*) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 

int _FAT_stat_r (struct _reent *r, const char *path, struct stat *st) {
	PARTITION* partition = NULL;
	DIR_ENTRY dirEntry;

	// Get the partition this file is on
	partition = _FAT_partition_getPartitionFromPath (path);
	if (partition == NULL) {
		r->_errno = ENODEV;
		return -1;
	}

	// Move the path pointer to the start of the actual path
	if (strchr (path, ':') != NULL) {
		path = strchr (path, ':') + 1;
	}
	if (strchr (path, ':') != NULL) {
		r->_errno = EINVAL;
		return -1;
	}

	_FAT_lock(&partition->lock);

	// Search for the file on the disc
	if (!_FAT_directory_entryFromPath (partition, &dirEntry, path, NULL)) {
		_FAT_unlock(&partition->lock);
		r->_errno = ENOENT;
		return -1;
	}

	// Fill in the stat struct
	_FAT_directory_entryStat (partition, &dirEntry, st);

	_FAT_unlock(&partition->lock);
	return 0;
}