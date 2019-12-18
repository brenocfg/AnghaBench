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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  force_compress; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_COMPRESS ; 
 int /*<<< orphan*/  BTRFS_INODE_HAS_ASYNC_EXTENT ; 
 int BTRFS_INODE_NODATACOW ; 
 int BTRFS_INODE_PREALLOC ; 
 int /*<<< orphan*/  COMPRESS ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int cow_file_range (struct inode*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,unsigned long*,int) ; 
 int cow_file_range_async (struct inode*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,unsigned long*) ; 
 int run_delalloc_nocow (struct inode*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,unsigned long*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_delalloc_range(struct inode *inode, struct page *locked_page,
			      u64 start, u64 end, int *page_started,
			      unsigned long *nr_written)
{
	int ret;
	struct btrfs_root *root = BTRFS_I(inode)->root;

	if (BTRFS_I(inode)->flags & BTRFS_INODE_NODATACOW) {
		ret = run_delalloc_nocow(inode, locked_page, start, end,
					 page_started, 1, nr_written);
	} else if (BTRFS_I(inode)->flags & BTRFS_INODE_PREALLOC) {
		ret = run_delalloc_nocow(inode, locked_page, start, end,
					 page_started, 0, nr_written);
	} else if (!btrfs_test_opt(root, COMPRESS) &&
		   !(BTRFS_I(inode)->force_compress) &&
		   !(BTRFS_I(inode)->flags & BTRFS_INODE_COMPRESS)) {
		ret = cow_file_range(inode, locked_page, start, end,
				      page_started, nr_written, 1);
	} else {
		set_bit(BTRFS_INODE_HAS_ASYNC_EXTENT,
			&BTRFS_I(inode)->runtime_flags);
		ret = cow_file_range_async(inode, locked_page, start, end,
					   page_started, nr_written);
	}
	return ret;
}