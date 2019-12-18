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
struct pohmelfs_inode {int /*<<< orphan*/  state; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETFS_INODE_REMOTE_SYNCED ; 
 struct pohmelfs_inode* POHMELFS_I (struct inode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  pohmelfs_put_inode (struct pohmelfs_inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pohmelfs_write_inode_complete(struct page **pages, unsigned int page_num,
		void *private, int err)
{
	struct inode *inode = private;
	struct pohmelfs_inode *pi = POHMELFS_I(inode);

	if (inode) {
		if (err) {
			mark_inode_dirty(inode);
			clear_bit(NETFS_INODE_REMOTE_SYNCED, &pi->state);
		} else {
			set_bit(NETFS_INODE_REMOTE_SYNCED, &pi->state);
		}

		pohmelfs_put_inode(pi);
	}

	return err;
}