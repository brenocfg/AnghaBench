#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_outstanding; int /*<<< orphan*/  plh_segs; int /*<<< orphan*/  plh_flags; scalar_t__ plh_block_lgets; scalar_t__ plh_barrier; } ;
struct TYPE_4__ {int /*<<< orphan*/  seqid; } ;
struct TYPE_5__ {TYPE_1__ stateid; } ;
typedef  TYPE_2__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LAYOUT_BULK_RECALL ; 
 int /*<<< orphan*/  NFS_LAYOUT_DESTROYED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
pnfs_layoutgets_blocked(struct pnfs_layout_hdr *lo, nfs4_stateid *stateid,
			int lget)
{
	if ((stateid) &&
	    (int)(lo->plh_barrier - be32_to_cpu(stateid->stateid.seqid)) >= 0)
		return true;
	return lo->plh_block_lgets ||
		test_bit(NFS_LAYOUT_DESTROYED, &lo->plh_flags) ||
		test_bit(NFS_LAYOUT_BULK_RECALL, &lo->plh_flags) ||
		(list_empty(&lo->plh_segs) &&
		 (atomic_read(&lo->plh_outstanding) > lget));
}