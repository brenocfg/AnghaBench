#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mru_cache_t ;
struct TYPE_9__ {int di_mode; } ;
struct TYPE_10__ {TYPE_5__* i_mount; int /*<<< orphan*/  i_ino; TYPE_1__ i_d; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct TYPE_11__ {int /*<<< orphan*/ * pip; int /*<<< orphan*/  ag; TYPE_2__* ip; } ;
typedef  TYPE_3__ fstrm_item_t ;
struct TYPE_12__ {int /*<<< orphan*/ * m_filestream; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NULLAGNUMBER ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  TRACE_LOOKUP (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int xfs_filestream_peek_ag (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_mru_cache_done (int /*<<< orphan*/ *) ; 
 TYPE_3__* xfs_mru_cache_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

xfs_agnumber_t
xfs_filestream_lookup_ag(
	xfs_inode_t	*ip)
{
	xfs_mru_cache_t	*cache;
	fstrm_item_t	*item;
	xfs_agnumber_t	ag;
	int		ref;

	if (!(ip->i_d.di_mode & (S_IFREG | S_IFDIR))) {
		ASSERT(0);
		return NULLAGNUMBER;
	}

	cache = ip->i_mount->m_filestream;
	item = xfs_mru_cache_lookup(cache, ip->i_ino);
	if (!item) {
		TRACE_LOOKUP(ip->i_mount, ip, NULL, NULLAGNUMBER, 0);
		return NULLAGNUMBER;
	}

	ASSERT(ip == item->ip);
	ag = item->ag;
	ref = xfs_filestream_peek_ag(ip->i_mount, ag);
	xfs_mru_cache_done(cache);

	TRACE_LOOKUP(ip->i_mount, ip, item->pip, ag, ref);
	return ag;
}