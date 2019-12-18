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
struct _reent {int /*<<< orphan*/  _errno; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ PARTITION ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOTDIR ; 
 scalar_t__ _FAT_directory_chdir (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__* _FAT_partition_getPartitionFromPath (char const*) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 

int _FAT_chdir_r (struct _reent *r, const char *path) {
	PARTITION* partition = NULL;

	// Get the partition this directory is on
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

	// Try changing directory
	if (_FAT_directory_chdir (partition, path)) {
		// Successful
		_FAT_unlock(&partition->lock);
		return 0;
	} else {
		// Failed
		_FAT_unlock(&partition->lock);
		r->_errno = ENOTDIR;
		return -1;
	}
}