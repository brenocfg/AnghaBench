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
struct v9fs_session_info {int /*<<< orphan*/  fscache; } ;
struct v9fs_cookie {int /*<<< orphan*/  lock; struct fscache_cookie* fscache; } ;
struct inode {int dummy; } ;
struct fscache_cookie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct inode*,struct fscache_cookie*,struct fscache_cookie*) ; 
 struct fscache_cookie* fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v9fs_cookie*) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (struct fscache_cookie*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_cache_inode_index_def ; 
 struct v9fs_cookie* v9fs_inode2cookie (struct inode*) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 

void v9fs_cache_inode_reset_cookie(struct inode *inode)
{
	struct v9fs_cookie *vcookie = v9fs_inode2cookie(inode);
	struct v9fs_session_info *v9ses;
	struct fscache_cookie *old;

	if (!vcookie->fscache)
		return;

	old = vcookie->fscache;

	spin_lock(&vcookie->lock);
	fscache_relinquish_cookie(vcookie->fscache, 1);

	v9ses = v9fs_inode2v9ses(inode);
	vcookie->fscache = fscache_acquire_cookie(v9ses->fscache,
						  &v9fs_cache_inode_index_def,
						  vcookie);

	P9_DPRINTK(P9_DEBUG_FSC, "inode %p revalidating cookie old %p new %p",
		   inode, old, vcookie->fscache);

	spin_unlock(&vcookie->lock);
}