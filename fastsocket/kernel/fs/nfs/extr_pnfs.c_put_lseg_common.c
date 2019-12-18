#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_segment {TYPE_1__* pls_layout; int /*<<< orphan*/  pls_list; int /*<<< orphan*/  pls_flags; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  roc_rpcwaitq; } ;
struct TYPE_3__ {int /*<<< orphan*/  plh_flags; int /*<<< orphan*/  plh_segs; struct inode* plh_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LAYOUT_DESTROYED ; 
 int /*<<< orphan*/  NFS_LSEG_VALID ; 
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  rpc_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
put_lseg_common(struct pnfs_layout_segment *lseg)
{
	struct inode *inode = lseg->pls_layout->plh_inode;

	WARN_ON(test_bit(NFS_LSEG_VALID, &lseg->pls_flags));
	list_del_init(&lseg->pls_list);
	if (list_empty(&lseg->pls_layout->plh_segs)) {
		set_bit(NFS_LAYOUT_DESTROYED, &lseg->pls_layout->plh_flags);
		/* Matched by initial refcount set in alloc_init_layout_hdr */
		pnfs_put_layout_hdr_locked(lseg->pls_layout);
	}
	rpc_wake_up(&NFS_SERVER(inode)->roc_rpcwaitq);
}