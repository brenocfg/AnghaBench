#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct TYPE_9__ {int /*<<< orphan*/  i_chain; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_total; int /*<<< orphan*/  i_used; } ;
struct TYPE_8__ {TYPE_2__ bitmap1; } ;
struct ocfs2_dinode {TYPE_4__ id2; TYPE_3__ id1; int /*<<< orphan*/  i_blkno; } ;
struct ocfs2_chain_list {TYPE_5__* cl_recs; int /*<<< orphan*/  cl_next_free_rec; } ;
struct ocfs2_alloc_context {scalar_t__ ac_bits_given; scalar_t__ ac_bits_wanted; size_t ac_chain; int ac_allow_chain_relink; scalar_t__ ac_last_group; TYPE_1__* ac_bh; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  c_free; } ;
struct TYPE_6__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__,scalar_t__) ; 
 size_t ocfs2_find_victim_chain (struct ocfs2_chain_list*) ; 
 int ocfs2_search_chain (struct ocfs2_alloc_context*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,size_t*,unsigned int*,scalar_t__*,size_t*) ; 
 int ocfs2_search_one_group (struct ocfs2_alloc_context*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,size_t*,unsigned int*,scalar_t__,size_t*) ; 

__attribute__((used)) static int ocfs2_claim_suballoc_bits(struct ocfs2_super *osb,
				     struct ocfs2_alloc_context *ac,
				     handle_t *handle,
				     u32 bits_wanted,
				     u32 min_bits,
				     u16 *bit_off,
				     unsigned int *num_bits,
				     u64 *bg_blkno)
{
	int status;
	u16 victim, i;
	u16 bits_left = 0;
	u64 hint_blkno = ac->ac_last_group;
	struct ocfs2_chain_list *cl;
	struct ocfs2_dinode *fe;

	mlog_entry_void();

	BUG_ON(ac->ac_bits_given >= ac->ac_bits_wanted);
	BUG_ON(bits_wanted > (ac->ac_bits_wanted - ac->ac_bits_given));
	BUG_ON(!ac->ac_bh);

	fe = (struct ocfs2_dinode *) ac->ac_bh->b_data;

	/* The bh was validated by the inode read during
	 * ocfs2_reserve_suballoc_bits().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));

	if (le32_to_cpu(fe->id1.bitmap1.i_used) >=
	    le32_to_cpu(fe->id1.bitmap1.i_total)) {
		ocfs2_error(osb->sb, "Chain allocator dinode %llu has %u used "
			    "bits but only %u total.",
			    (unsigned long long)le64_to_cpu(fe->i_blkno),
			    le32_to_cpu(fe->id1.bitmap1.i_used),
			    le32_to_cpu(fe->id1.bitmap1.i_total));
		status = -EIO;
		goto bail;
	}

	if (hint_blkno) {
		/* Attempt to short-circuit the usual search mechanism
		 * by jumping straight to the most recently used
		 * allocation group. This helps us mantain some
		 * contiguousness across allocations. */
		status = ocfs2_search_one_group(ac, handle, bits_wanted,
						min_bits, bit_off, num_bits,
						hint_blkno, &bits_left);
		if (!status) {
			/* Be careful to update *bg_blkno here as the
			 * caller is expecting it to be filled in, and
			 * ocfs2_search_one_group() won't do that for
			 * us. */
			*bg_blkno = hint_blkno;
			goto set_hint;
		}
		if (status < 0 && status != -ENOSPC) {
			mlog_errno(status);
			goto bail;
		}
	}

	cl = (struct ocfs2_chain_list *) &fe->id2.i_chain;

	victim = ocfs2_find_victim_chain(cl);
	ac->ac_chain = victim;
	ac->ac_allow_chain_relink = 1;

	status = ocfs2_search_chain(ac, handle, bits_wanted, min_bits, bit_off,
				    num_bits, bg_blkno, &bits_left);
	if (!status)
		goto set_hint;
	if (status < 0 && status != -ENOSPC) {
		mlog_errno(status);
		goto bail;
	}

	mlog(0, "Search of victim chain %u came up with nothing, "
	     "trying all chains now.\n", victim);

	/* If we didn't pick a good victim, then just default to
	 * searching each chain in order. Don't allow chain relinking
	 * because we only calculate enough journal credits for one
	 * relink per alloc. */
	ac->ac_allow_chain_relink = 0;
	for (i = 0; i < le16_to_cpu(cl->cl_next_free_rec); i ++) {
		if (i == victim)
			continue;
		if (!cl->cl_recs[i].c_free)
			continue;

		ac->ac_chain = i;
		status = ocfs2_search_chain(ac, handle, bits_wanted, min_bits,
					    bit_off, num_bits, bg_blkno,
					    &bits_left);
		if (!status)
			break;
		if (status < 0 && status != -ENOSPC) {
			mlog_errno(status);
			goto bail;
		}
	}

set_hint:
	if (status != -ENOSPC) {
		/* If the next search of this group is not likely to
		 * yield a suitable extent, then we reset the last
		 * group hint so as to not waste a disk read */
		if (bits_left < min_bits)
			ac->ac_last_group = 0;
		else
			ac->ac_last_group = *bg_blkno;
	}

bail:
	mlog_exit(status);
	return status;
}