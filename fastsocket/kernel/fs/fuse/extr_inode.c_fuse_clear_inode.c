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
struct inode {TYPE_1__* i_sb; } ;
struct fuse_inode {int /*<<< orphan*/ * forget_req; int /*<<< orphan*/  nlookup; int /*<<< orphan*/  nodeid; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 int MS_ACTIVE ; 
 int /*<<< orphan*/  fuse_send_forget (struct fuse_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 

__attribute__((used)) static void fuse_clear_inode(struct inode *inode)
{
	if (inode->i_sb->s_flags & MS_ACTIVE) {
		struct fuse_conn *fc = get_fuse_conn(inode);
		struct fuse_inode *fi = get_fuse_inode(inode);
		fuse_send_forget(fc, fi->forget_req, fi->nodeid, fi->nlookup);
		fi->forget_req = NULL;
	}
}