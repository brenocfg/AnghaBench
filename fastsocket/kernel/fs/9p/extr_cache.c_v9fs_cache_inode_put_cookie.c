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
struct v9fs_cookie {int /*<<< orphan*/ * fscache; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct v9fs_cookie* v9fs_inode2cookie (struct inode*) ; 

void v9fs_cache_inode_put_cookie(struct inode *inode)
{
	struct v9fs_cookie *vcookie = v9fs_inode2cookie(inode);

	if (!vcookie->fscache)
		return;
	P9_DPRINTK(P9_DEBUG_FSC, "inode %p put cookie %p", inode,
		   vcookie->fscache);

	fscache_relinquish_cookie(vcookie->fscache, 0);
	vcookie->fscache = NULL;
}