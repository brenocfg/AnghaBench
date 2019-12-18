#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int nilfs_mdt_create_block (struct inode*,unsigned long,struct buffer_head**,void (*) (struct inode*,struct buffer_head*,void*)) ; 
 int nilfs_mdt_read_block (struct inode*,unsigned long,struct buffer_head**) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_mdt_get_block(struct inode *inode, unsigned long blkoff, int create,
			void (*init_block)(struct inode *,
					   struct buffer_head *, void *),
			struct buffer_head **out_bh)
{
	int ret;

	/* Should be rewritten with merging nilfs_mdt_read_block() */
 retry:
	ret = nilfs_mdt_read_block(inode, blkoff, out_bh);
	if (!create || ret != -ENOENT)
		return ret;

	ret = nilfs_mdt_create_block(inode, blkoff, out_bh, init_block);
	if (unlikely(ret == -EEXIST)) {
		/* create = 0; */  /* limit read-create loop retries */
		goto retry;
	}
	return ret;
}