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
struct nilfs_snapshot_list {void* ssl_next; void* ssl_prev; } ;
struct nilfs_cpfile_header {int /*<<< orphan*/  ch_nsnapshots; struct nilfs_snapshot_list ch_snapshot_list; } ;
struct nilfs_checkpoint {struct nilfs_snapshot_list cp_snapshot_list; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  KM_USER0 ; 
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_add_cpu (int /*<<< orphan*/ *,int) ; 
 scalar_t__ le64_to_cpu (void*) ; 
 scalar_t__ nilfs_checkpoint_invalid (struct nilfs_checkpoint*) ; 
 int /*<<< orphan*/  nilfs_checkpoint_set_snapshot (struct nilfs_checkpoint*) ; 
 scalar_t__ nilfs_checkpoint_snapshot (struct nilfs_checkpoint*) ; 
 struct nilfs_checkpoint* nilfs_cpfile_block_get_checkpoint (struct inode*,scalar_t__,struct buffer_head*,void*) ; 
 struct nilfs_cpfile_header* nilfs_cpfile_block_get_header (struct inode*,struct buffer_head*,void*) ; 
 struct nilfs_snapshot_list* nilfs_cpfile_block_get_snapshot_list (struct inode*,scalar_t__,struct buffer_head*,void*) ; 
 unsigned long nilfs_cpfile_get_blkoff (struct inode*,scalar_t__) ; 
 int nilfs_cpfile_get_checkpoint_block (struct inode*,scalar_t__,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int nilfs_cpfile_get_header_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_cpfile_set_snapshot(struct inode *cpfile, __u64 cno)
{
	struct buffer_head *header_bh, *curr_bh, *prev_bh, *cp_bh;
	struct nilfs_cpfile_header *header;
	struct nilfs_checkpoint *cp;
	struct nilfs_snapshot_list *list;
	__u64 curr, prev;
	unsigned long curr_blkoff, prev_blkoff;
	void *kaddr;
	int ret;

	if (cno == 0)
		return -ENOENT; /* checkpoint number 0 is invalid */
	down_write(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_checkpoint_block(cpfile, cno, 0, &cp_bh);
	if (ret < 0)
		goto out_sem;
	kaddr = kmap_atomic(cp_bh->b_page, KM_USER0);
	cp = nilfs_cpfile_block_get_checkpoint(cpfile, cno, cp_bh, kaddr);
	if (nilfs_checkpoint_invalid(cp)) {
		ret = -ENOENT;
		kunmap_atomic(kaddr, KM_USER0);
		goto out_cp;
	}
	if (nilfs_checkpoint_snapshot(cp)) {
		ret = 0;
		kunmap_atomic(kaddr, KM_USER0);
		goto out_cp;
	}
	kunmap_atomic(kaddr, KM_USER0);

	ret = nilfs_cpfile_get_header_block(cpfile, &header_bh);
	if (ret < 0)
		goto out_cp;
	kaddr = kmap_atomic(header_bh->b_page, KM_USER0);
	header = nilfs_cpfile_block_get_header(cpfile, header_bh, kaddr);
	list = &header->ch_snapshot_list;
	curr_bh = header_bh;
	get_bh(curr_bh);
	curr = 0;
	curr_blkoff = 0;
	prev = le64_to_cpu(list->ssl_prev);
	while (prev > cno) {
		prev_blkoff = nilfs_cpfile_get_blkoff(cpfile, prev);
		curr = prev;
		if (curr_blkoff != prev_blkoff) {
			kunmap_atomic(kaddr, KM_USER0);
			brelse(curr_bh);
			ret = nilfs_cpfile_get_checkpoint_block(cpfile, curr,
								0, &curr_bh);
			if (ret < 0)
				goto out_header;
			kaddr = kmap_atomic(curr_bh->b_page, KM_USER0);
		}
		curr_blkoff = prev_blkoff;
		cp = nilfs_cpfile_block_get_checkpoint(
			cpfile, curr, curr_bh, kaddr);
		list = &cp->cp_snapshot_list;
		prev = le64_to_cpu(list->ssl_prev);
	}
	kunmap_atomic(kaddr, KM_USER0);

	if (prev != 0) {
		ret = nilfs_cpfile_get_checkpoint_block(cpfile, prev, 0,
							&prev_bh);
		if (ret < 0)
			goto out_curr;
	} else {
		prev_bh = header_bh;
		get_bh(prev_bh);
	}

	kaddr = kmap_atomic(curr_bh->b_page, KM_USER0);
	list = nilfs_cpfile_block_get_snapshot_list(
		cpfile, curr, curr_bh, kaddr);
	list->ssl_prev = cpu_to_le64(cno);
	kunmap_atomic(kaddr, KM_USER0);

	kaddr = kmap_atomic(cp_bh->b_page, KM_USER0);
	cp = nilfs_cpfile_block_get_checkpoint(cpfile, cno, cp_bh, kaddr);
	cp->cp_snapshot_list.ssl_next = cpu_to_le64(curr);
	cp->cp_snapshot_list.ssl_prev = cpu_to_le64(prev);
	nilfs_checkpoint_set_snapshot(cp);
	kunmap_atomic(kaddr, KM_USER0);

	kaddr = kmap_atomic(prev_bh->b_page, KM_USER0);
	list = nilfs_cpfile_block_get_snapshot_list(
		cpfile, prev, prev_bh, kaddr);
	list->ssl_next = cpu_to_le64(cno);
	kunmap_atomic(kaddr, KM_USER0);

	kaddr = kmap_atomic(header_bh->b_page, KM_USER0);
	header = nilfs_cpfile_block_get_header(cpfile, header_bh, kaddr);
	le64_add_cpu(&header->ch_nsnapshots, 1);
	kunmap_atomic(kaddr, KM_USER0);

	nilfs_mdt_mark_buffer_dirty(prev_bh);
	nilfs_mdt_mark_buffer_dirty(curr_bh);
	nilfs_mdt_mark_buffer_dirty(cp_bh);
	nilfs_mdt_mark_buffer_dirty(header_bh);
	nilfs_mdt_mark_dirty(cpfile);

	brelse(prev_bh);

 out_curr:
	brelse(curr_bh);

 out_header:
	brelse(header_bh);

 out_cp:
	brelse(cp_bh);

 out_sem:
	up_write(&NILFS_MDT(cpfile)->mi_sem);
	return ret;
}