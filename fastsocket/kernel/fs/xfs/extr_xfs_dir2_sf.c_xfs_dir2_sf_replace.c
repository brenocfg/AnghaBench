#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/ * if_data; } ;
struct TYPE_29__ {int if_flags; scalar_t__ if_bytes; TYPE_2__ if_u1; } ;
struct TYPE_27__ {scalar_t__ di_size; } ;
struct TYPE_31__ {TYPE_3__ i_df; TYPE_1__ i_d; int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_5__ xfs_inode_t ;
typedef  scalar_t__ xfs_ino_t ;
struct TYPE_30__ {int i8count; int count; int /*<<< orphan*/  parent; } ;
struct TYPE_32__ {TYPE_4__ hdr; } ;
typedef  TYPE_6__ xfs_dir2_sf_t ;
struct TYPE_33__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ xfs_dir2_sf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_ino8_t ;
typedef  int /*<<< orphan*/  xfs_dir2_ino4_t ;
struct TYPE_34__ {scalar_t__ inumber; int namelen; char* name; int op_flags; int /*<<< orphan*/  trans; TYPE_5__* dp; } ;
typedef  TYPE_8__ xfs_da_args_t ;
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ XFS_CMP_EXACT ; 
 int XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_DIR2_MAX_SHORT_INUM ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int XFS_IFINLINE ; 
 int XFS_IFORK_DSIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  XFS_ILOG_DDATA ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent ; 
 int /*<<< orphan*/  trace_xfs_dir2_sf_replace (TYPE_8__*) ; 
 scalar_t__ xfs_da_compname (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_dir2_block_replace (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_check (TYPE_8__*) ; 
 TYPE_7__* xfs_dir2_sf_firstentry (TYPE_6__*) ; 
 scalar_t__ xfs_dir2_sf_get_inumber (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_dir2_sf_hdr_size (int) ; 
 int /*<<< orphan*/  xfs_dir2_sf_hdr_t ; 
 int /*<<< orphan*/ * xfs_dir2_sf_inumberp (TYPE_7__*) ; 
 TYPE_7__* xfs_dir2_sf_nextentry (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_put_inumber (TYPE_6__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int xfs_dir2_sf_to_block (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_toino4 (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_toino8 (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_sf_replace(
	xfs_da_args_t		*args)		/* operation arguments */
{
	xfs_inode_t		*dp;		/* incore directory inode */
	int			i;		/* entry index */
#if XFS_BIG_INUMS || defined(DEBUG)
	xfs_ino_t		ino=0;		/* entry old inode number */
#endif
#if XFS_BIG_INUMS
	int			i8elevated;	/* sf_toino8 set i8count=1 */
#endif
	xfs_dir2_sf_entry_t	*sfep;		/* shortform directory entry */
	xfs_dir2_sf_t		*sfp;		/* shortform structure */

	trace_xfs_dir2_sf_replace(args);

	dp = args->dp;

	ASSERT(dp->i_df.if_flags & XFS_IFINLINE);
	/*
	 * Bail out if the shortform directory is way too small.
	 */
	if (dp->i_d.di_size < offsetof(xfs_dir2_sf_hdr_t, parent)) {
		ASSERT(XFS_FORCED_SHUTDOWN(dp->i_mount));
		return XFS_ERROR(EIO);
	}
	ASSERT(dp->i_df.if_bytes == dp->i_d.di_size);
	ASSERT(dp->i_df.if_u1.if_data != NULL);
	sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
	ASSERT(dp->i_d.di_size >= xfs_dir2_sf_hdr_size(sfp->hdr.i8count));
#if XFS_BIG_INUMS
	/*
	 * New inode number is large, and need to convert to 8-byte inodes.
	 */
	if (args->inumber > XFS_DIR2_MAX_SHORT_INUM && sfp->hdr.i8count == 0) {
		int	error;			/* error return value */
		int	newsize;		/* new inode size */

		newsize =
			dp->i_df.if_bytes +
			(sfp->hdr.count + 1) *
			((uint)sizeof(xfs_dir2_ino8_t) -
			 (uint)sizeof(xfs_dir2_ino4_t));
		/*
		 * Won't fit as shortform, convert to block then do replace.
		 */
		if (newsize > XFS_IFORK_DSIZE(dp)) {
			error = xfs_dir2_sf_to_block(args);
			if (error) {
				return error;
			}
			return xfs_dir2_block_replace(args);
		}
		/*
		 * Still fits, convert to 8-byte now.
		 */
		xfs_dir2_sf_toino8(args);
		i8elevated = 1;
		sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
	} else
		i8elevated = 0;
#endif
	ASSERT(args->namelen != 1 || args->name[0] != '.');
	/*
	 * Replace ..'s entry.
	 */
	if (args->namelen == 2 &&
	    args->name[0] == '.' && args->name[1] == '.') {
#if XFS_BIG_INUMS || defined(DEBUG)
		ino = xfs_dir2_sf_get_inumber(sfp, &sfp->hdr.parent);
		ASSERT(args->inumber != ino);
#endif
		xfs_dir2_sf_put_inumber(sfp, &args->inumber, &sfp->hdr.parent);
	}
	/*
	 * Normal entry, look for the name.
	 */
	else {
		for (i = 0, sfep = xfs_dir2_sf_firstentry(sfp);
				i < sfp->hdr.count;
				i++, sfep = xfs_dir2_sf_nextentry(sfp, sfep)) {
			if (xfs_da_compname(args, sfep->name, sfep->namelen) ==
								XFS_CMP_EXACT) {
#if XFS_BIG_INUMS || defined(DEBUG)
				ino = xfs_dir2_sf_get_inumber(sfp,
					xfs_dir2_sf_inumberp(sfep));
				ASSERT(args->inumber != ino);
#endif
				xfs_dir2_sf_put_inumber(sfp, &args->inumber,
					xfs_dir2_sf_inumberp(sfep));
				break;
			}
		}
		/*
		 * Didn't find it.
		 */
		if (i == sfp->hdr.count) {
			ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
#if XFS_BIG_INUMS
			if (i8elevated)
				xfs_dir2_sf_toino4(args);
#endif
			return XFS_ERROR(ENOENT);
		}
	}
#if XFS_BIG_INUMS
	/*
	 * See if the old number was large, the new number is small.
	 */
	if (ino > XFS_DIR2_MAX_SHORT_INUM &&
	    args->inumber <= XFS_DIR2_MAX_SHORT_INUM) {
		/*
		 * And the old count was one, so need to convert to small.
		 */
		if (sfp->hdr.i8count == 1)
			xfs_dir2_sf_toino4(args);
		else
			sfp->hdr.i8count--;
	}
	/*
	 * See if the old number was small, the new number is large.
	 */
	if (ino <= XFS_DIR2_MAX_SHORT_INUM &&
	    args->inumber > XFS_DIR2_MAX_SHORT_INUM) {
		/*
		 * add to the i8count unless we just converted to 8-byte
		 * inodes (which does an implied i8count = 1)
		 */
		ASSERT(sfp->hdr.i8count != 0);
		if (!i8elevated)
			sfp->hdr.i8count++;
	}
#endif
	xfs_dir2_sf_check(args);
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_DDATA);
	return 0;
}