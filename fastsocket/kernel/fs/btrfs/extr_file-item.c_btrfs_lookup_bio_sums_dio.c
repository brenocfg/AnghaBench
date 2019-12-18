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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int __btrfs_lookup_bio_sums (struct btrfs_root*,struct inode*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int btrfs_lookup_bio_sums_dio(struct btrfs_root *root, struct inode *inode,
			      struct bio *bio, u64 offset, u32 *dst)
{
	return __btrfs_lookup_bio_sums(root, inode, bio, offset, dst, 1);
}