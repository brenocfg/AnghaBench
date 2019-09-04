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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct nfs_vattr {int dummy; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 int ESTALE ; 
 int nfs_getattr_internal (int /*<<< orphan*/ ,struct nfs_vattr*,int /*<<< orphan*/ ,int) ; 
 int nfs_refresh_fh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfs_getattr(nfsnode_t np, struct nfs_vattr *nvap, vfs_context_t ctx, int flags)
{
	int error;
	
retry:
	error = nfs_getattr_internal(np, nvap, ctx, flags);
	if (error == ESTALE) {
		error = nfs_refresh_fh(np, ctx);
		if (!error)
			goto retry;
	}
	return (error);
}