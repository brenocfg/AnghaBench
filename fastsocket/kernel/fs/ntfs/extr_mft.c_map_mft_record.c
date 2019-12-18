#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* vol; int /*<<< orphan*/  count; int /*<<< orphan*/  mrec_lock; int /*<<< orphan*/  mft_no; } ;
typedef  TYPE_2__ ntfs_inode ;
struct TYPE_5__ {int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  MFT_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * map_mft_record_page (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfs_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

MFT_RECORD *map_mft_record(ntfs_inode *ni)
{
	MFT_RECORD *m;

	ntfs_debug("Entering for mft_no 0x%lx.", ni->mft_no);

	/* Make sure the ntfs inode doesn't go away. */
	atomic_inc(&ni->count);

	/* Serialize access to this mft record. */
	mutex_lock(&ni->mrec_lock);

	m = map_mft_record_page(ni);
	if (likely(!IS_ERR(m)))
		return m;

	mutex_unlock(&ni->mrec_lock);
	atomic_dec(&ni->count);
	ntfs_error(ni->vol->sb, "Failed with error code %lu.", -PTR_ERR(m));
	return m;
}