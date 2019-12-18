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
struct xfs_perag {int /*<<< orphan*/  pag_agno; int /*<<< orphan*/  pag_mount; int /*<<< orphan*/  pag_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_perag_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
xfs_perag_put(struct xfs_perag *pag)
{
	int	ref;

	ASSERT(atomic_read(&pag->pag_ref) > 0);
	ref = atomic_dec_return(&pag->pag_ref);
	trace_xfs_perag_put(pag->pag_mount, pag->pag_agno, ref, _RET_IP_);
}