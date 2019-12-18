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
typedef  unsigned long u16 ;
struct compressed_bio {int dummy; } ;
struct btrfs_root {unsigned long sectorsize; TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  super_copy; } ;

/* Variables and functions */
 unsigned long btrfs_super_csum_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int compressed_bio_size(struct btrfs_root *root,
				      unsigned long disk_size)
{
	u16 csum_size = btrfs_super_csum_size(root->fs_info->super_copy);

	return sizeof(struct compressed_bio) +
		((disk_size + root->sectorsize - 1) / root->sectorsize) *
		csum_size;
}