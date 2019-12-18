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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_lc_cred; struct inode* plh_inode; int /*<<< orphan*/  plh_bulk_recall; int /*<<< orphan*/  plh_segs; int /*<<< orphan*/  plh_layouts; int /*<<< orphan*/  plh_refcount; } ;
struct nfs_open_context {TYPE_2__* state; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {TYPE_1__* owner; } ;
struct TYPE_3__ {int /*<<< orphan*/  so_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_rpccred (int /*<<< orphan*/ ) ; 
 struct pnfs_layout_hdr* pnfs_alloc_layout_hdr (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pnfs_layout_hdr *
alloc_init_layout_hdr(struct inode *ino,
		      struct nfs_open_context *ctx,
		      gfp_t gfp_flags)
{
	struct pnfs_layout_hdr *lo;

	lo = pnfs_alloc_layout_hdr(ino, gfp_flags);
	if (!lo)
		return NULL;
	atomic_set(&lo->plh_refcount, 1);
	INIT_LIST_HEAD(&lo->plh_layouts);
	INIT_LIST_HEAD(&lo->plh_segs);
	INIT_LIST_HEAD(&lo->plh_bulk_recall);
	lo->plh_inode = ino;
	lo->plh_lc_cred = get_rpccred(ctx->state->owner->so_cred);
	return lo;
}