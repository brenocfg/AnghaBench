#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mru_cache_t ;
struct TYPE_19__ {int /*<<< orphan*/ * m_filestream; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_18__ {int di_mode; } ;
struct TYPE_20__ {int /*<<< orphan*/  i_ino; TYPE_2__* i_mount; TYPE_1__ i_d; } ;
typedef  TYPE_3__ xfs_inode_t ;
typedef  scalar_t__ xfs_agnumber_t ;
struct TYPE_21__ {scalar_t__ ag; TYPE_3__* pip; TYPE_3__* ip; } ;
typedef  TYPE_4__ fstrm_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IHOLD (TYPE_3__*) ; 
 int /*<<< orphan*/  IRELE (TYPE_3__*) ; 
 int /*<<< orphan*/  KM_MAYFAIL ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  TRACE_UPDATE (TYPE_2__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_zone ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_filestream_get_ag (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_filestream_peek_ag (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_filestream_put_ag (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_mru_cache_done (int /*<<< orphan*/ *) ; 
 int xfs_mru_cache_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* xfs_mru_cache_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_xfs_filestream_update_ag(
	xfs_inode_t	*ip,
	xfs_inode_t	*pip,
	xfs_agnumber_t	ag)
{
	int		err = 0;
	xfs_mount_t	*mp;
	xfs_mru_cache_t	*cache;
	fstrm_item_t	*item;
	xfs_agnumber_t	old_ag;
	xfs_inode_t	*old_pip;

	/*
	 * Either ip is a regular file and pip is a directory, or ip is a
	 * directory and pip is NULL.
	 */
	ASSERT(ip && (((ip->i_d.di_mode & S_IFREG) && pip &&
	               (pip->i_d.di_mode & S_IFDIR)) ||
	              ((ip->i_d.di_mode & S_IFDIR) && !pip)));

	mp = ip->i_mount;
	cache = mp->m_filestream;

	item = xfs_mru_cache_lookup(cache, ip->i_ino);
	if (item) {
		ASSERT(item->ip == ip);
		old_ag = item->ag;
		item->ag = ag;
		old_pip = item->pip;
		item->pip = pip;
		xfs_mru_cache_done(cache);

		/*
		 * If the AG has changed, drop the old ref and take a new one,
		 * effectively transferring the reference from old to new AG.
		 */
		if (ag != old_ag) {
			xfs_filestream_put_ag(mp, old_ag);
			xfs_filestream_get_ag(mp, ag);
		}

		/*
		 * If ip is a file and its pip has changed, drop the old ref and
		 * take a new one.
		 */
		if (pip && pip != old_pip) {
			IRELE(old_pip);
			IHOLD(pip);
		}

		TRACE_UPDATE(mp, ip, old_ag, xfs_filestream_peek_ag(mp, old_ag),
				ag, xfs_filestream_peek_ag(mp, ag));
		return 0;
	}

	item = kmem_zone_zalloc(item_zone, KM_MAYFAIL);
	if (!item)
		return ENOMEM;

	item->ag = ag;
	item->ip = ip;
	item->pip = pip;

	err = xfs_mru_cache_insert(cache, ip->i_ino, item);
	if (err) {
		kmem_zone_free(item_zone, item);
		return err;
	}

	/* Take a reference on the AG. */
	xfs_filestream_get_ag(mp, ag);

	/*
	 * Take a reference on the inode itself regardless of whether it's a
	 * regular file or a directory.
	 */
	IHOLD(ip);

	/*
	 * In the case of a regular file, take a reference on the parent inode
	 * as well to ensure it remains in-core.
	 */
	if (pip)
		IHOLD(pip);

	TRACE_UPDATE(mp, ip, ag, xfs_filestream_peek_ag(mp, ag),
			ag, xfs_filestream_peek_ag(mp, ag));

	return 0;
}