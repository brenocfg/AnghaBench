#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ di_size; } ;
struct TYPE_23__ {int /*<<< orphan*/ * if_data; } ;
struct TYPE_25__ {int if_flags; scalar_t__ if_bytes; TYPE_1__ if_u1; } ;
struct TYPE_29__ {TYPE_22__* i_mount; void* i_ino; TYPE_3__ i_d; TYPE_2__ i_df; } ;
typedef  TYPE_6__ xfs_inode_t ;
struct TYPE_27__ {int count; int /*<<< orphan*/  parent; int /*<<< orphan*/  i8count; } ;
struct TYPE_30__ {TYPE_4__ hdr; } ;
typedef  TYPE_7__ xfs_dir2_sf_t ;
struct TYPE_31__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_8__ xfs_dir2_sf_entry_t ;
struct TYPE_32__ {int namelen; char* name; int cmpresult; int op_flags; void* inumber; TYPE_6__* dp; } ;
typedef  TYPE_9__ xfs_da_args_t ;
typedef  enum xfs_dacmp { ____Placeholder_xfs_dacmp } xfs_dacmp ;
struct TYPE_28__ {int (* compname ) (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_24__ {TYPE_5__* m_dirnameops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EEXIST ; 
 int EIO ; 
 int ENOENT ; 
 int XFS_CMP_DIFFERENT ; 
 int XFS_CMP_EXACT ; 
 int XFS_DA_OP_OKNOENT ; 
 int XFS_ERROR (int) ; 
 int XFS_FORCED_SHUTDOWN (TYPE_22__*) ; 
 int XFS_IFINLINE ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent ; 
 int stub1 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_dir2_sf_lookup (TYPE_9__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_check (TYPE_9__*) ; 
 TYPE_8__* xfs_dir2_sf_firstentry (TYPE_7__*) ; 
 void* xfs_dir2_sf_get_inumber (TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_dir2_sf_hdr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_sf_hdr_t ; 
 int /*<<< orphan*/ * xfs_dir2_sf_inumberp (TYPE_8__*) ; 
 TYPE_8__* xfs_dir2_sf_nextentry (TYPE_7__*,TYPE_8__*) ; 
 int xfs_dir_cilookup_result (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_sf_lookup(
	xfs_da_args_t		*args)		/* operation arguments */
{
	xfs_inode_t		*dp;		/* incore directory inode */
	int			i;		/* entry index */
	int			error;
	xfs_dir2_sf_entry_t	*sfep;		/* shortform directory entry */
	xfs_dir2_sf_t		*sfp;		/* shortform structure */
	enum xfs_dacmp		cmp;		/* comparison result */
	xfs_dir2_sf_entry_t	*ci_sfep;	/* case-insens. entry */

	trace_xfs_dir2_sf_lookup(args);

	xfs_dir2_sf_check(args);
	dp = args->dp;

	ASSERT(dp->i_df.if_flags & XFS_IFINLINE);
	/*
	 * Bail out if the directory is way too short.
	 */
	if (dp->i_d.di_size < offsetof(xfs_dir2_sf_hdr_t, parent)) {
		ASSERT(XFS_FORCED_SHUTDOWN(dp->i_mount));
		return XFS_ERROR(EIO);
	}
	ASSERT(dp->i_df.if_bytes == dp->i_d.di_size);
	ASSERT(dp->i_df.if_u1.if_data != NULL);
	sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
	ASSERT(dp->i_d.di_size >= xfs_dir2_sf_hdr_size(sfp->hdr.i8count));
	/*
	 * Special case for .
	 */
	if (args->namelen == 1 && args->name[0] == '.') {
		args->inumber = dp->i_ino;
		args->cmpresult = XFS_CMP_EXACT;
		return XFS_ERROR(EEXIST);
	}
	/*
	 * Special case for ..
	 */
	if (args->namelen == 2 &&
	    args->name[0] == '.' && args->name[1] == '.') {
		args->inumber = xfs_dir2_sf_get_inumber(sfp, &sfp->hdr.parent);
		args->cmpresult = XFS_CMP_EXACT;
		return XFS_ERROR(EEXIST);
	}
	/*
	 * Loop over all the entries trying to match ours.
	 */
	ci_sfep = NULL;
	for (i = 0, sfep = xfs_dir2_sf_firstentry(sfp); i < sfp->hdr.count;
				i++, sfep = xfs_dir2_sf_nextentry(sfp, sfep)) {
		/*
		 * Compare name and if it's an exact match, return the inode
		 * number. If it's the first case-insensitive match, store the
		 * inode number and continue looking for an exact match.
		 */
		cmp = dp->i_mount->m_dirnameops->compname(args, sfep->name,
								sfep->namelen);
		if (cmp != XFS_CMP_DIFFERENT && cmp != args->cmpresult) {
			args->cmpresult = cmp;
			args->inumber = xfs_dir2_sf_get_inumber(sfp,
						xfs_dir2_sf_inumberp(sfep));
			if (cmp == XFS_CMP_EXACT)
				return XFS_ERROR(EEXIST);
			ci_sfep = sfep;
		}
	}
	ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
	/*
	 * Here, we can only be doing a lookup (not a rename or replace).
	 * If a case-insensitive match was not found, return ENOENT.
	 */
	if (!ci_sfep)
		return XFS_ERROR(ENOENT);
	/* otherwise process the CI match as required by the caller */
	error = xfs_dir_cilookup_result(args, ci_sfep->name, ci_sfep->namelen);
	return XFS_ERROR(error);
}