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
struct nilfs_segment_usage {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 void* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_segment_usage_error (struct nilfs_segment_usage*) ; 
 struct nilfs_segment_usage* nilfs_sufile_block_get_segment_usage (struct inode*,scalar_t__,struct buffer_head*,void*) ; 
 scalar_t__ nilfs_sufile_get_nsegments (struct inode*) ; 
 int nilfs_sufile_get_segment_usage_block (struct inode*,scalar_t__,int,struct buffer_head**) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nilfs_sufile_get_segment_usage(struct inode *sufile, __u64 segnum,
				   struct nilfs_segment_usage **sup,
				   struct buffer_head **bhp)
{
	struct buffer_head *bh;
	struct nilfs_segment_usage *su;
	void *kaddr;
	int ret;

	/* segnum is 0 origin */
	if (segnum >= nilfs_sufile_get_nsegments(sufile))
		return -EINVAL;
	down_write(&NILFS_MDT(sufile)->mi_sem);
	ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 1, &bh);
	if (ret < 0)
		goto out_sem;
	kaddr = kmap(bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, bh, kaddr);
	if (nilfs_segment_usage_error(su)) {
		kunmap(bh->b_page);
		brelse(bh);
		ret = -EINVAL;
		goto out_sem;
	}

	if (sup != NULL)
		*sup = su;
	*bhp = bh;

 out_sem:
	up_write(&NILFS_MDT(sufile)->mi_sem);
	return ret;
}