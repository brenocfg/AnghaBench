#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {int /*<<< orphan*/  rd_gl; } ;
struct gfs2_rbm {struct gfs2_rgrpd* rgd; TYPE_1__* bi; } ;
struct TYPE_4__ {scalar_t__ b_data; int /*<<< orphan*/  b_size; } ;
struct TYPE_3__ {TYPE_2__* bi_bh; int /*<<< orphan*/  bi_len; scalar_t__ bi_offset; scalar_t__ bi_clone; } ;

/* Variables and functions */
 int GFP_NOFS ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,unsigned long long) ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,scalar_t__,int) ; 
 scalar_t__ gfs2_consist (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_rbm_from_block (struct gfs2_rbm*,scalar_t__) ; 
 int /*<<< orphan*/  gfs2_setbit (struct gfs2_rbm*,int,unsigned char) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ kmalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gfs2_rgrpd *rgblk_free(struct gfs2_sbd *sdp, u64 bstart,
				     u32 blen, unsigned char new_state)
{
	struct gfs2_rbm rbm;

	rbm.rgd = gfs2_blk2rgrpd(sdp, bstart, 1);
	if (!rbm.rgd) {
		if (gfs2_consist(sdp))
			fs_err(sdp, "block = %llu\n", (unsigned long long)bstart);
		return NULL;
	}

	while (blen--) {
		gfs2_rbm_from_block(&rbm, bstart);
		bstart++;
		if (!rbm.bi->bi_clone) {
			rbm.bi->bi_clone = kmalloc(rbm.bi->bi_bh->b_size,
						   GFP_NOFS | __GFP_NOFAIL);
			memcpy(rbm.bi->bi_clone + rbm.bi->bi_offset,
			       rbm.bi->bi_bh->b_data + rbm.bi->bi_offset,
			       rbm.bi->bi_len);
		}
		gfs2_trans_add_meta(rbm.rgd->rd_gl, rbm.bi->bi_bh);
		gfs2_setbit(&rbm, false, new_state);
	}

	return rbm.rgd;
}