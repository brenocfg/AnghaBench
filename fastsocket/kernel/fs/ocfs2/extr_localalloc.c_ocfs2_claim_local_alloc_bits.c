#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ocfs2_super {TYPE_3__* local_alloc_bh; } ;
struct ocfs2_local_alloc {int /*<<< orphan*/  la_bm_off; void* la_bitmap; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_used; } ;
struct TYPE_6__ {TYPE_1__ bitmap1; } ;
struct ocfs2_dinode {TYPE_2__ id1; } ;
struct ocfs2_alloc_context {scalar_t__ ac_which; struct inode* ac_inode; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_7__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ OCFS2_AC_USE_LOCAL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_local_alloc* OCFS2_LOCAL_ALLOC (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int ocfs2_local_alloc_find_clear_bits (struct ocfs2_super*,struct ocfs2_dinode*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_set_bit (int /*<<< orphan*/ ,void*) ; 

int ocfs2_claim_local_alloc_bits(struct ocfs2_super *osb,
				 handle_t *handle,
				 struct ocfs2_alloc_context *ac,
				 u32 bits_wanted,
				 u32 *bit_off,
				 u32 *num_bits)
{
	int status, start;
	struct inode *local_alloc_inode;
	void *bitmap;
	struct ocfs2_dinode *alloc;
	struct ocfs2_local_alloc *la;

	mlog_entry_void();
	BUG_ON(ac->ac_which != OCFS2_AC_USE_LOCAL);

	local_alloc_inode = ac->ac_inode;
	alloc = (struct ocfs2_dinode *) osb->local_alloc_bh->b_data;
	la = OCFS2_LOCAL_ALLOC(alloc);

	start = ocfs2_local_alloc_find_clear_bits(osb, alloc, bits_wanted);
	if (start == -1) {
		/* TODO: Shouldn't we just BUG here? */
		status = -ENOSPC;
		mlog_errno(status);
		goto bail;
	}

	bitmap = la->la_bitmap;
	*bit_off = le32_to_cpu(la->la_bm_off) + start;
	/* local alloc is always contiguous by nature -- we never
	 * delete bits from it! */
	*num_bits = bits_wanted;

	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(local_alloc_inode),
					 osb->local_alloc_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	while(bits_wanted--)
		ocfs2_set_bit(start++, bitmap);

	le32_add_cpu(&alloc->id1.bitmap1.i_used, *num_bits);

	status = ocfs2_journal_dirty(handle, osb->local_alloc_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = 0;
bail:
	mlog_exit(status);
	return status;
}