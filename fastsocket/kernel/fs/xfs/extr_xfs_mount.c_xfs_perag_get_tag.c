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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_perag {int /*<<< orphan*/  pag_agno; int /*<<< orphan*/  pag_ref; } ;
struct xfs_mount {int /*<<< orphan*/  m_perag_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int radix_tree_gang_lookup_tag (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  trace_xfs_perag_get_tag (struct xfs_mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct xfs_perag *
xfs_perag_get_tag(
	struct xfs_mount	*mp,
	xfs_agnumber_t		first,
	int			tag)
{
	struct xfs_perag	*pag;
	int			found;
	int			ref;

	rcu_read_lock();
	found = radix_tree_gang_lookup_tag(&mp->m_perag_tree,
					(void **)&pag, first, 1, tag);
	if (found <= 0) {
		rcu_read_unlock();
		return NULL;
	}
	ref = atomic_inc_return(&pag->pag_ref);
	rcu_read_unlock();
	trace_xfs_perag_get_tag(mp, pag->pag_agno, ref, _RET_IP_);
	return pag;
}