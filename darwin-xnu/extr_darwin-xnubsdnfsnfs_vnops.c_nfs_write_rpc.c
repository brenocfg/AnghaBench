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
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 int nfs_write_rpc2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs_write_rpc(
	nfsnode_t np,
	uio_t uio,
	vfs_context_t ctx,
	int *iomodep,
	uint64_t *wverfp)
{
	return nfs_write_rpc2(np, uio, vfs_context_thread(ctx), vfs_context_ucred(ctx), iomodep, wverfp);
}