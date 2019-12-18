#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct gfs2_rbm {scalar_t__ offset; TYPE_1__* rgd; struct gfs2_bitmap* bi; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_extent {scalar_t__ len; struct gfs2_rbm rbm; } ;
struct gfs2_bitmap {int bi_offset; int /*<<< orphan*/  bi_flags; int /*<<< orphan*/ * bi_clone; struct buffer_head* bi_bh; } ;
struct gfs2_alloc_parms {int dummy; } ;
struct buffer_head {int /*<<< orphan*/ * b_data; } ;
struct TYPE_2__ {int rd_length; scalar_t__ rd_extfail_pt; struct gfs2_bitmap* rd_bits; } ;

/* Variables and functions */
 scalar_t__ BFITNOENT ; 
 int E2BIG ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GBF_FULL ; 
 int /*<<< orphan*/  GFS2_BLKST_FREE ; 
 int /*<<< orphan*/  GFS2_BLKST_UNLINKED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ gfs2_bitfit (int /*<<< orphan*/ *,struct gfs2_bitmap*,scalar_t__,int /*<<< orphan*/ ) ; 
 int gfs2_reservation_check_and_update (struct gfs2_rbm*,struct gfs2_inode const*,scalar_t__,struct gfs2_extent*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_rbm_find(struct gfs2_rbm *rbm, u8 state, u32 *minext,
			 const struct gfs2_inode *ip, bool nowrap,
			 const struct gfs2_alloc_parms *ap)
{
	struct buffer_head *bh;
	struct gfs2_bitmap *initial_bi;
	u32 initial_offset;
	struct gfs2_bitmap *first_bi = rbm->bi;
	u32 first_offset = rbm->offset;
	u32 offset;
	u8 *buffer;
	int index;
	int n = 0;
	int iters = rbm->rgd->rd_length;
	int ret;
	struct gfs2_extent maxext = { .rbm.rgd = rbm->rgd, };

	/* If we are not starting at the beginning of a bitmap, then we
	 * need to add one to the bitmap count to ensure that we search
	 * the starting bitmap twice.
	 */
	if (rbm->offset != 0)
		iters++;

	while(1) {
		if (test_bit(GBF_FULL, &rbm->bi->bi_flags) &&
		    (state == GFS2_BLKST_FREE))
			goto next_bitmap;

		bh = rbm->bi->bi_bh;
		buffer = bh->b_data + rbm->bi->bi_offset;
		WARN_ON(!buffer_uptodate(bh));
		if (state != GFS2_BLKST_UNLINKED && rbm->bi->bi_clone)
			buffer = rbm->bi->bi_clone + rbm->bi->bi_offset;
		initial_offset = rbm->offset;
		offset = gfs2_bitfit(buffer, rbm->bi, rbm->offset, state);
		if (offset == BFITNOENT)
			goto bitmap_full;
		rbm->offset = offset;
		if (ip == NULL)
			return 0;

		initial_bi = rbm->bi;
		ret = gfs2_reservation_check_and_update(rbm, ip,
							minext ? *minext : 0,
							&maxext);
		if (ret == 0)
			return 0;
		if (ret > 0) {
			n += (rbm->bi - initial_bi);
			goto next_iter;
		}
		if (ret == -E2BIG) {
			index = 0;
			rbm->offset = 0;
			n += (rbm->bi - initial_bi);
			goto res_covered_end_of_rgrp;
		}
		return ret;

bitmap_full:	/* Mark bitmap as full and fall through */
		if ((state == GFS2_BLKST_FREE) && initial_offset == 0)
			set_bit(GBF_FULL, &rbm->bi->bi_flags);

next_bitmap:	/* Find next bitmap in the rgrp */
		rbm->offset = 0;
		index = rbm->bi - rbm->rgd->rd_bits;
		index++;
		if (index == rbm->rgd->rd_length)
			index = 0;
res_covered_end_of_rgrp:
		rbm->bi = &rbm->rgd->rd_bits[index];
		if ((index == 0) && nowrap)
			break;
		n++;
next_iter:
		if (n >= iters)
			break;
	}

	if (minext == NULL || state != GFS2_BLKST_FREE)
		return -ENOSPC;

	/* If the extent was too small, and it's smaller than the smallest
	   to have failed before, remember for future reference that it's
	   useless to search this rgrp again for this amount or more. */
	if ((first_offset == 0) && (first_bi == rbm->rgd->rd_bits) &&
	    (*minext < rbm->rgd->rd_extfail_pt))
		rbm->rgd->rd_extfail_pt = *minext;

	/* If the maximum extent we found is big enough to fulfill the
	   minimum requirements, use it anyway. */
	if (maxext.len) {
		*rbm = maxext.rbm;
		*minext = maxext.len;
		return 0;
	}

	return -ENOSPC;
}