#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_1__* NTFS_I (struct inode*) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_big_inode_cache ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 

void ntfs_destroy_big_inode(struct inode *inode)
{
	ntfs_inode *ni = NTFS_I(inode);

	ntfs_debug("Entering.");
	BUG_ON(ni->page);
	if (!atomic_dec_and_test(&ni->count))
		BUG();
	kmem_cache_free(ntfs_big_inode_cache, NTFS_I(inode));
}