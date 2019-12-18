#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ const vcn; int length; scalar_t__ lcn; } ;
typedef  TYPE_3__ runlist_element ;
struct TYPE_13__ {TYPE_3__* rl; } ;
struct TYPE_16__ {TYPE_2__* vol; TYPE_1__ runlist; int /*<<< orphan*/  size_lock; int /*<<< orphan*/  allocated_size; int /*<<< orphan*/  mft_no; } ;
typedef  TYPE_4__ ntfs_inode ;
struct TYPE_17__ {int /*<<< orphan*/  mrec; } ;
typedef  TYPE_5__ ntfs_attr_search_ctx ;
typedef  scalar_t__ VCN ;
struct TYPE_14__ {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 TYPE_3__* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ LCN_ENOENT ; 
 scalar_t__ LCN_HOLE ; 
 scalar_t__ LCN_RL_NOT_MAPPED ; 
 int /*<<< orphan*/  NInoNonResident (TYPE_4__*) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,int) ; 
 int ntfs_map_runlist_nolock (TYPE_4__*,scalar_t__ const,TYPE_5__*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

runlist_element *ntfs_attr_find_vcn_nolock(ntfs_inode *ni, const VCN vcn,
		ntfs_attr_search_ctx *ctx)
{
	unsigned long flags;
	runlist_element *rl;
	int err = 0;
	bool is_retry = false;

	ntfs_debug("Entering for i_ino 0x%lx, vcn 0x%llx, with%s ctx.",
			ni->mft_no, (unsigned long long)vcn, ctx ? "" : "out");
	BUG_ON(!ni);
	BUG_ON(!NInoNonResident(ni));
	BUG_ON(vcn < 0);
	if (!ni->runlist.rl) {
		read_lock_irqsave(&ni->size_lock, flags);
		if (!ni->allocated_size) {
			read_unlock_irqrestore(&ni->size_lock, flags);
			return ERR_PTR(-ENOENT);
		}
		read_unlock_irqrestore(&ni->size_lock, flags);
	}
retry_remap:
	rl = ni->runlist.rl;
	if (likely(rl && vcn >= rl[0].vcn)) {
		while (likely(rl->length)) {
			if (unlikely(vcn < rl[1].vcn)) {
				if (likely(rl->lcn >= LCN_HOLE)) {
					ntfs_debug("Done.");
					return rl;
				}
				break;
			}
			rl++;
		}
		if (likely(rl->lcn != LCN_RL_NOT_MAPPED)) {
			if (likely(rl->lcn == LCN_ENOENT))
				err = -ENOENT;
			else
				err = -EIO;
		}
	}
	if (!err && !is_retry) {
		/*
		 * If the search context is invalid we cannot map the unmapped
		 * region.
		 */
		if (IS_ERR(ctx->mrec))
			err = PTR_ERR(ctx->mrec);
		else {
			/*
			 * The @vcn is in an unmapped region, map the runlist
			 * and retry.
			 */
			err = ntfs_map_runlist_nolock(ni, vcn, ctx);
			if (likely(!err)) {
				is_retry = true;
				goto retry_remap;
			}
		}
		if (err == -EINVAL)
			err = -EIO;
	} else if (!err)
		err = -EIO;
	if (err != -ENOENT)
		ntfs_error(ni->vol->sb, "Failed with error code %i.", err);
	return ERR_PTR(err);
}