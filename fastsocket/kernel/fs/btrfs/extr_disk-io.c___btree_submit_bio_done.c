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
struct inode {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int btrfs_map_bio (int /*<<< orphan*/ ,int,struct bio*,int,int) ; 

__attribute__((used)) static int __btree_submit_bio_done(struct inode *inode, int rw, struct bio *bio,
				 int mirror_num, unsigned long bio_flags,
				 u64 bio_offset)
{
	/*
	 * when we're called for a write, we're already in the async
	 * submission context.  Just jump into btrfs_map_bio
	 */
	return btrfs_map_bio(BTRFS_I(inode)->root, rw, bio, mirror_num, 1);
}