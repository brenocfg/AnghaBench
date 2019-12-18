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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int REQ_WRITE ; 
 int /*<<< orphan*/  __btrfs_submit_bio_done ; 
 int /*<<< orphan*/  __btrfs_submit_bio_start_direct_io ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int btrfs_bio_wq_end_io (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ) ; 
 int btrfs_csum_one_bio (struct btrfs_root*,struct inode*,struct bio*,int /*<<< orphan*/ ,int) ; 
 int btrfs_lookup_bio_sums_dio (struct btrfs_root*,struct inode*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int btrfs_map_bio (struct btrfs_root*,int,struct bio*,int /*<<< orphan*/ ,int) ; 
 int btrfs_wq_submit_bio (int /*<<< orphan*/ ,struct inode*,int,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __btrfs_submit_dio_bio(struct bio *bio, struct inode *inode,
					 int rw, u64 file_offset, int skip_sum,
					 u32 *csums, int async_submit)
{
	int write = rw & REQ_WRITE;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int ret;

	bio_get(bio);

	if (!write) {
		ret = btrfs_bio_wq_end_io(root->fs_info, bio, 0);
		if (ret)
			goto err;
	}

	if (skip_sum)
		goto map;

	if (write && async_submit) {
		ret = btrfs_wq_submit_bio(root->fs_info,
				   inode, rw, bio, 0, 0,
				   file_offset,
				   __btrfs_submit_bio_start_direct_io,
				   __btrfs_submit_bio_done);
		goto err;
	} else if (write) {
		/*
		 * If we aren't doing async submit, calculate the csum of the
		 * bio now.
		 */
		ret = btrfs_csum_one_bio(root, inode, bio, file_offset, 1);
		if (ret)
			goto err;
	} else if (!skip_sum) {
		ret = btrfs_lookup_bio_sums_dio(root, inode, bio,
					  file_offset, csums);
		if (ret)
			goto err;
	}

map:
	ret = btrfs_map_bio(root, rw, bio, 0, async_submit);
err:
	bio_put(bio);
	return ret;
}