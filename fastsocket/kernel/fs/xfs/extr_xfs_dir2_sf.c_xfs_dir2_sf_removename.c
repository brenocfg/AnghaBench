#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/ * if_data; } ;
struct TYPE_26__ {int if_flags; int if_bytes; TYPE_2__ if_u1; } ;
struct TYPE_24__ {int di_size; } ;
struct TYPE_28__ {TYPE_3__ i_df; TYPE_1__ i_d; int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_5__ xfs_inode_t ;
struct TYPE_27__ {int i8count; int count; } ;
struct TYPE_29__ {TYPE_4__ hdr; } ;
typedef  TYPE_6__ xfs_dir2_sf_t ;
struct TYPE_30__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ xfs_dir2_sf_entry_t ;
struct TYPE_31__ {scalar_t__ inumber; int /*<<< orphan*/  trans; int /*<<< orphan*/  namelen; TYPE_5__* dp; } ;
typedef  TYPE_8__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ XFS_CMP_EXACT ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DIR2_MAX_SHORT_INUM ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int XFS_IFINLINE ; 
 int XFS_ILOG_CORE ; 
 int XFS_ILOG_DDATA ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent ; 
 int /*<<< orphan*/  trace_xfs_dir2_sf_removename (TYPE_8__*) ; 
 scalar_t__ xfs_da_compname (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_sf_check (TYPE_8__*) ; 
 int xfs_dir2_sf_entsize_byname (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* xfs_dir2_sf_firstentry (TYPE_6__*) ; 
 scalar_t__ xfs_dir2_sf_get_inumber (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int xfs_dir2_sf_hdr_size (int) ; 
 int /*<<< orphan*/  xfs_dir2_sf_hdr_t ; 
 int /*<<< orphan*/  xfs_dir2_sf_inumberp (TYPE_7__*) ; 
 TYPE_7__* xfs_dir2_sf_nextentry (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_toino4 (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_idata_realloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ ,TYPE_5__*,int) ; 

int						/* error */
xfs_dir2_sf_removename(
	xfs_da_args_t		*args)
{
	int			byteoff;	/* offset of removed entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			entsize;	/* this entry's size */
	int			i;		/* shortform entry index */
	int			newsize;	/* new inode size */
	int			oldsize;	/* old inode size */
	xfs_dir2_sf_entry_t	*sfep;		/* shortform directory entry */
	xfs_dir2_sf_t		*sfp;		/* shortform structure */

	trace_xfs_dir2_sf_removename(args);

	dp = args->dp;

	ASSERT(dp->i_df.if_flags & XFS_IFINLINE);
	oldsize = (int)dp->i_d.di_size;
	/*
	 * Bail out if the directory is way too short.
	 */
	if (oldsize < offsetof(xfs_dir2_sf_hdr_t, parent)) {
		ASSERT(XFS_FORCED_SHUTDOWN(dp->i_mount));
		return XFS_ERROR(EIO);
	}
	ASSERT(dp->i_df.if_bytes == oldsize);
	ASSERT(dp->i_df.if_u1.if_data != NULL);
	sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
	ASSERT(oldsize >= xfs_dir2_sf_hdr_size(sfp->hdr.i8count));
	/*
	 * Loop over the old directory entries.
	 * Find the one we're deleting.
	 */
	for (i = 0, sfep = xfs_dir2_sf_firstentry(sfp); i < sfp->hdr.count;
				i++, sfep = xfs_dir2_sf_nextentry(sfp, sfep)) {
		if (xfs_da_compname(args, sfep->name, sfep->namelen) ==
								XFS_CMP_EXACT) {
			ASSERT(xfs_dir2_sf_get_inumber(sfp,
						xfs_dir2_sf_inumberp(sfep)) ==
								args->inumber);
			break;
		}
	}
	/*
	 * Didn't find it.
	 */
	if (i == sfp->hdr.count)
		return XFS_ERROR(ENOENT);
	/*
	 * Calculate sizes.
	 */
	byteoff = (int)((char *)sfep - (char *)sfp);
	entsize = xfs_dir2_sf_entsize_byname(sfp, args->namelen);
	newsize = oldsize - entsize;
	/*
	 * Copy the part if any after the removed entry, sliding it down.
	 */
	if (byteoff + entsize < oldsize)
		memmove((char *)sfp + byteoff, (char *)sfp + byteoff + entsize,
			oldsize - (byteoff + entsize));
	/*
	 * Fix up the header and file size.
	 */
	sfp->hdr.count--;
	dp->i_d.di_size = newsize;
	/*
	 * Reallocate, making it smaller.
	 */
	xfs_idata_realloc(dp, newsize - oldsize, XFS_DATA_FORK);
	sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
#if XFS_BIG_INUMS
	/*
	 * Are we changing inode number size?
	 */
	if (args->inumber > XFS_DIR2_MAX_SHORT_INUM) {
		if (sfp->hdr.i8count == 1)
			xfs_dir2_sf_toino4(args);
		else
			sfp->hdr.i8count--;
	}
#endif
	xfs_dir2_sf_check(args);
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_DDATA);
	return 0;
}