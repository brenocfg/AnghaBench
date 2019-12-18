#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ di_aformat; } ;
struct TYPE_13__ {TYPE_1__ i_d; TYPE_4__* i_afp; } ;
typedef  TYPE_3__ xfs_inode_t ;
struct TYPE_12__ {scalar_t__ if_data; } ;
struct TYPE_14__ {scalar_t__ if_bytes; int if_flags; TYPE_2__ if_u1; } ;
typedef  TYPE_4__ xfs_ifork_t ;
struct TYPE_15__ {int /*<<< orphan*/  trans; TYPE_3__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_16__ {int /*<<< orphan*/  totsize; scalar_t__ count; } ;
typedef  TYPE_6__ xfs_attr_sf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 scalar_t__ XFS_DINODE_FMT_EXTENTS ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int XFS_IFEXTENTS ; 
 int XFS_IFINLINE ; 
 int XFS_ILOG_ADATA ; 
 int XFS_ILOG_CORE ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  trace_xfs_attr_sf_create (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_idata_realloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ ,TYPE_3__*,int) ; 

void
xfs_attr_shortform_create(xfs_da_args_t *args)
{
	xfs_attr_sf_hdr_t *hdr;
	xfs_inode_t *dp;
	xfs_ifork_t *ifp;

	trace_xfs_attr_sf_create(args);

	dp = args->dp;
	ASSERT(dp != NULL);
	ifp = dp->i_afp;
	ASSERT(ifp != NULL);
	ASSERT(ifp->if_bytes == 0);
	if (dp->i_d.di_aformat == XFS_DINODE_FMT_EXTENTS) {
		ifp->if_flags &= ~XFS_IFEXTENTS;	/* just in case */
		dp->i_d.di_aformat = XFS_DINODE_FMT_LOCAL;
		ifp->if_flags |= XFS_IFINLINE;
	} else {
		ASSERT(ifp->if_flags & XFS_IFINLINE);
	}
	xfs_idata_realloc(dp, sizeof(*hdr), XFS_ATTR_FORK);
	hdr = (xfs_attr_sf_hdr_t *)ifp->if_u1.if_data;
	hdr->count = 0;
	hdr->totsize = cpu_to_be16(sizeof(*hdr));
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_ADATA);
}