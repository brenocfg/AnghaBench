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
struct nfs_sync_cargs {int waitfor; int error; int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  mount_t ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_sync_callout ; 
 int /*<<< orphan*/  vnode_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs_sync_cargs*) ; 

int
nfs_vfs_sync(mount_t mp, int waitfor, vfs_context_t ctx)
{
	struct nfs_sync_cargs cargs;

	cargs.waitfor = waitfor;
	cargs.ctx = ctx;
	cargs.error = 0;

	vnode_iterate(mp, 0, nfs_sync_callout, &cargs);

	return (cargs.error);
}