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
struct pnfs_layout_segment {struct pnfs_layout_hdr* pls_layout; int /*<<< orphan*/  pls_flags; int /*<<< orphan*/  pls_refcount; int /*<<< orphan*/  pls_lc_list; int /*<<< orphan*/  pls_list; } ;
struct pnfs_layout_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_LSEG_VALID ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void
init_lseg(struct pnfs_layout_hdr *lo, struct pnfs_layout_segment *lseg)
{
	INIT_LIST_HEAD(&lseg->pls_list);
	INIT_LIST_HEAD(&lseg->pls_lc_list);
	atomic_set(&lseg->pls_refcount, 1);
	smp_mb();
	set_bit(NFS_LSEG_VALID, &lseg->pls_flags);
	lseg->pls_layout = lo;
}