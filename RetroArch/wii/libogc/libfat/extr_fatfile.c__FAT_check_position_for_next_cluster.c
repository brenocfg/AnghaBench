#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct _reent {int /*<<< orphan*/  _errno; } ;
struct TYPE_9__ {scalar_t__ sector; scalar_t__ cluster; } ;
struct TYPE_8__ {scalar_t__ sectorsPerCluster; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ FILE_POSITION ;

/* Variables and functions */
 scalar_t__ CLUSTER_EOF ; 
 scalar_t__ CLUSTER_FREE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  _FAT_fat_isValidCluster (TYPE_1__*,scalar_t__) ; 
 scalar_t__ _FAT_fat_linkFreeCluster (TYPE_1__*,scalar_t__) ; 
 scalar_t__ _FAT_fat_nextCluster (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static bool _FAT_check_position_for_next_cluster(struct _reent *r,
		FILE_POSITION *position, PARTITION* partition, size_t remain, bool *flagNoError)
{
	uint32_t tempNextCluster;
	// do nothing if no more data to write
	if (remain == 0) return true;
	if (flagNoError && *flagNoError == false) return false;
	if (position->sector > partition->sectorsPerCluster) {
		// invalid arguments - internal error
		r->_errno = EINVAL;
		goto err;
	}
	if (position->sector == partition->sectorsPerCluster) {
		// need to advance to next cluster
		tempNextCluster = _FAT_fat_nextCluster(partition, position->cluster);
		if ((tempNextCluster == CLUSTER_EOF) || (tempNextCluster == CLUSTER_FREE)) {
			// Ran out of clusters so get a new one
			tempNextCluster = _FAT_fat_linkFreeCluster(partition, position->cluster);
		}
		if (!_FAT_fat_isValidCluster(partition, tempNextCluster)) {
			// Couldn't get a cluster, so abort
			r->_errno = ENOSPC;
			goto err;
		}
		position->sector = 0;
		position->cluster = tempNextCluster;
	}
	return true;
err:
	if (flagNoError) *flagNoError = false;
	return false;
}