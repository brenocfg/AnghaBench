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
struct page {int dummy; } ;
struct io_ctl {int num_pages; int check_crcs; struct btrfs_root* root; int /*<<< orphan*/  pages; } ;
struct inode {int dummy; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FREE_INO_OBJECTID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ btrfs_ino (struct inode*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct io_ctl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int io_ctl_init(struct io_ctl *io_ctl, struct inode *inode,
		       struct btrfs_root *root)
{
	memset(io_ctl, 0, sizeof(struct io_ctl));
	io_ctl->num_pages = (i_size_read(inode) + PAGE_CACHE_SIZE - 1) >>
		PAGE_CACHE_SHIFT;
	io_ctl->pages = kzalloc(sizeof(struct page *) * io_ctl->num_pages,
				GFP_NOFS);
	if (!io_ctl->pages)
		return -ENOMEM;
	io_ctl->root = root;
	if (btrfs_ino(inode) != BTRFS_FREE_INO_OBJECTID)
		io_ctl->check_crcs = 1;
	return 0;
}