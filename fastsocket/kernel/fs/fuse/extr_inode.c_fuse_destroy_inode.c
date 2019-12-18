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
struct fuse_inode {scalar_t__ forget_req; int /*<<< orphan*/  queued_writes; int /*<<< orphan*/  write_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  fuse_inode_cachep ; 
 int /*<<< orphan*/  fuse_request_free (scalar_t__) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_destroy_inode(struct inode *inode)
{
	struct fuse_inode *fi = get_fuse_inode(inode);
	BUG_ON(!list_empty(&fi->write_files));
	BUG_ON(!list_empty(&fi->queued_writes));
	if (fi->forget_req)
		fuse_request_free(fi->forget_req);
	kmem_cache_free(fuse_inode_cachep, inode);
}