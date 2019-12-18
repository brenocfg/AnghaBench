#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  rl; } ;
struct TYPE_9__ {TYPE_2__* vol; TYPE_1__ runlist; int /*<<< orphan*/  size_lock; int /*<<< orphan*/  allocated_size; int /*<<< orphan*/  mft_no; } ;
typedef  TYPE_3__ ntfs_inode ;
typedef  scalar_t__ VCN ;
struct TYPE_8__ {int /*<<< orphan*/  sb; } ;
typedef  scalar_t__ LCN ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ LCN_EIO ; 
 scalar_t__ LCN_ENOENT ; 
 scalar_t__ LCN_ENOMEM ; 
 scalar_t__ LCN_HOLE ; 
 scalar_t__ LCN_RL_NOT_MAPPED ; 
 int /*<<< orphan*/  NInoNonResident (TYPE_3__*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ntfs_debug (char*,long long,...) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,long long) ; 
 int ntfs_map_runlist_nolock (TYPE_3__*,scalar_t__ const,int /*<<< orphan*/ *) ; 
 scalar_t__ ntfs_rl_vcn_to_lcn (int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

LCN ntfs_attr_vcn_to_lcn_nolock(ntfs_inode *ni, const VCN vcn,
		const bool write_locked)
{
	LCN lcn;
	unsigned long flags;
	bool is_retry = false;

	ntfs_debug("Entering for i_ino 0x%lx, vcn 0x%llx, %s_locked.",
			ni->mft_no, (unsigned long long)vcn,
			write_locked ? "write" : "read");
	BUG_ON(!ni);
	BUG_ON(!NInoNonResident(ni));
	BUG_ON(vcn < 0);
	if (!ni->runlist.rl) {
		read_lock_irqsave(&ni->size_lock, flags);
		if (!ni->allocated_size) {
			read_unlock_irqrestore(&ni->size_lock, flags);
			return LCN_ENOENT;
		}
		read_unlock_irqrestore(&ni->size_lock, flags);
	}
retry_remap:
	/* Convert vcn to lcn.  If that fails map the runlist and retry once. */
	lcn = ntfs_rl_vcn_to_lcn(ni->runlist.rl, vcn);
	if (likely(lcn >= LCN_HOLE)) {
		ntfs_debug("Done, lcn 0x%llx.", (long long)lcn);
		return lcn;
	}
	if (lcn != LCN_RL_NOT_MAPPED) {
		if (lcn != LCN_ENOENT)
			lcn = LCN_EIO;
	} else if (!is_retry) {
		int err;

		if (!write_locked) {
			up_read(&ni->runlist.lock);
			down_write(&ni->runlist.lock);
			if (unlikely(ntfs_rl_vcn_to_lcn(ni->runlist.rl, vcn) !=
					LCN_RL_NOT_MAPPED)) {
				up_write(&ni->runlist.lock);
				down_read(&ni->runlist.lock);
				goto retry_remap;
			}
		}
		err = ntfs_map_runlist_nolock(ni, vcn, NULL);
		if (!write_locked) {
			up_write(&ni->runlist.lock);
			down_read(&ni->runlist.lock);
		}
		if (likely(!err)) {
			is_retry = true;
			goto retry_remap;
		}
		if (err == -ENOENT)
			lcn = LCN_ENOENT;
		else if (err == -ENOMEM)
			lcn = LCN_ENOMEM;
		else
			lcn = LCN_EIO;
	}
	if (lcn != LCN_ENOENT)
		ntfs_error(ni->vol->sb, "Failed with error code %lli.",
				(long long)lcn);
	return lcn;
}