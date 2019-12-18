#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  m_ddev_targp; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
typedef  scalar_t__ xfs_dablk_t ;
struct TYPE_11__ {int flags; int valuelen; int /*<<< orphan*/  rmtblkcnt; TYPE_5__* dp; int /*<<< orphan*/  trans; scalar_t__ rmtblkno; void* value; } ;
typedef  TYPE_2__ xfs_da_args_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
struct TYPE_12__ {scalar_t__ br_startblock; scalar_t__ br_blockcount; } ;
typedef  TYPE_3__ xfs_bmbt_irec_t ;
struct TYPE_13__ {TYPE_1__* i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_KERNOVAL ; 
 int ATTR_RMTVALUE_MAPSIZE ; 
 scalar_t__ DELAYSTARTBLOCK ; 
 scalar_t__ HOLESTARTBLOCK ; 
 int XBF_DONT_BLOCK ; 
 int XBF_LOCK ; 
 int /*<<< orphan*/  XBRW_READ ; 
 int XFS_BMAPI_ATTRFORK ; 
 int XFS_BMAPI_METADATA ; 
 int XFS_BUF_SIZE (int /*<<< orphan*/ *) ; 
 int XFS_FSB_TO_BB (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (TYPE_1__*,scalar_t__) ; 
 int xfs_bmapi (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_iomove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_relse (int /*<<< orphan*/ *) ; 
 int xfs_read_buf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **) ; 

int
xfs_attr_rmtval_get(xfs_da_args_t *args)
{
	xfs_bmbt_irec_t map[ATTR_RMTVALUE_MAPSIZE];
	xfs_mount_t *mp;
	xfs_daddr_t dblkno;
	void *dst;
	xfs_buf_t *bp;
	int nmap, error, tmp, valuelen, blkcnt, i;
	xfs_dablk_t lblkno;

	ASSERT(!(args->flags & ATTR_KERNOVAL));

	mp = args->dp->i_mount;
	dst = args->value;
	valuelen = args->valuelen;
	lblkno = args->rmtblkno;
	while (valuelen > 0) {
		nmap = ATTR_RMTVALUE_MAPSIZE;
		error = xfs_bmapi(args->trans, args->dp, (xfs_fileoff_t)lblkno,
				  args->rmtblkcnt,
				  XFS_BMAPI_ATTRFORK | XFS_BMAPI_METADATA,
				  NULL, 0, map, &nmap, NULL);
		if (error)
			return(error);
		ASSERT(nmap >= 1);

		for (i = 0; (i < nmap) && (valuelen > 0); i++) {
			ASSERT((map[i].br_startblock != DELAYSTARTBLOCK) &&
			       (map[i].br_startblock != HOLESTARTBLOCK));
			dblkno = XFS_FSB_TO_DADDR(mp, map[i].br_startblock);
			blkcnt = XFS_FSB_TO_BB(mp, map[i].br_blockcount);
			error = xfs_read_buf(mp, mp->m_ddev_targp, dblkno,
					     blkcnt, XBF_LOCK | XBF_DONT_BLOCK,
					     &bp);
			if (error)
				return(error);

			tmp = (valuelen < XFS_BUF_SIZE(bp))
				? valuelen : XFS_BUF_SIZE(bp);
			xfs_buf_iomove(bp, 0, tmp, dst, XBRW_READ);
			xfs_buf_relse(bp);
			dst += tmp;
			valuelen -= tmp;

			lblkno += map[i].br_blockcount;
		}
	}
	ASSERT(valuelen == 0);
	return(0);
}