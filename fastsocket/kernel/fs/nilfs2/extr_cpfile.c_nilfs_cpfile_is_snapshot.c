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
struct nilfs_checkpoint {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  KM_USER0 ; 
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_checkpoint_invalid (struct nilfs_checkpoint*) ; 
 int nilfs_checkpoint_snapshot (struct nilfs_checkpoint*) ; 
 struct nilfs_checkpoint* nilfs_cpfile_block_get_checkpoint (struct inode*,scalar_t__,struct buffer_head*,void*) ; 
 int nilfs_cpfile_get_checkpoint_block (struct inode*,scalar_t__,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ nilfs_mdt_cno (struct inode*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_cpfile_is_snapshot(struct inode *cpfile, __u64 cno)
{
	struct buffer_head *bh;
	struct nilfs_checkpoint *cp;
	void *kaddr;
	int ret;

	/* CP number is invalid if it's zero or larger than the
	largest	exist one.*/
	if (cno == 0 || cno >= nilfs_mdt_cno(cpfile))
		return -ENOENT;
	down_read(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_checkpoint_block(cpfile, cno, 0, &bh);
	if (ret < 0)
		goto out;
	kaddr = kmap_atomic(bh->b_page, KM_USER0);
	cp = nilfs_cpfile_block_get_checkpoint(cpfile, cno, bh, kaddr);
	if (nilfs_checkpoint_invalid(cp))
		ret = -ENOENT;
	else
		ret = nilfs_checkpoint_snapshot(cp);
	kunmap_atomic(kaddr, KM_USER0);
	brelse(bh);

 out:
	up_read(&NILFS_MDT(cpfile)->mi_sem);
	return ret;
}