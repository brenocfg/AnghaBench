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
struct v9fs_cookie {scalar_t__ fscache; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v9fs_cookie*) ; 
 int /*<<< orphan*/  v9fs_cache_inode_index_def ; 
 struct v9fs_cookie* v9fs_inode2cookie (struct inode*) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 

void v9fs_cache_inode_get_cookie(struct inode *inode)
{
	struct v9fs_cookie *vcookie;
	struct v9fs_session_info *v9ses;

	if (!S_ISREG(inode->i_mode))
		return;

	vcookie = v9fs_inode2cookie(inode);
	if (vcookie->fscache)
		return;

	v9ses = v9fs_inode2v9ses(inode);
	vcookie->fscache = fscache_acquire_cookie(v9ses->fscache,
						  &v9fs_cache_inode_index_def,
						  vcookie);

	P9_DPRINTK(P9_DEBUG_FSC, "inode %p get cookie %p", inode,
		   vcookie->fscache);
}