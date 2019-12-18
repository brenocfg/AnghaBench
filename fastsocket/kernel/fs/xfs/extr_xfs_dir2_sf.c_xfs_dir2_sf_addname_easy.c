#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int di_size; } ;
struct TYPE_17__ {scalar_t__ if_data; } ;
struct TYPE_18__ {TYPE_1__ if_u1; } ;
struct TYPE_21__ {TYPE_4__ i_d; TYPE_2__ i_df; } ;
typedef  TYPE_5__ xfs_inode_t ;
struct TYPE_19__ {int /*<<< orphan*/  i8count; int /*<<< orphan*/  count; } ;
struct TYPE_22__ {TYPE_3__ hdr; } ;
typedef  TYPE_6__ xfs_dir2_sf_t ;
struct TYPE_23__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ xfs_dir2_sf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct TYPE_24__ {scalar_t__ inumber; int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; TYPE_5__* dp; } ;
typedef  TYPE_8__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DIR2_MAX_SHORT_INUM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_sf_check (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_entsize_byname (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_sf_inumberp (TYPE_7__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_put_inumber (TYPE_6__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_sf_put_offset (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_idata_realloc (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir2_sf_addname_easy(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_dir2_sf_entry_t	*sfep,		/* pointer to new entry */
	xfs_dir2_data_aoff_t	offset,		/* offset to use for new ent */
	int			new_isize)	/* new directory size */
{
	int			byteoff;	/* byte offset in sf dir */
	xfs_inode_t		*dp;		/* incore directory inode */
	xfs_dir2_sf_t		*sfp;		/* shortform structure */

	dp = args->dp;

	sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
	byteoff = (int)((char *)sfep - (char *)sfp);
	/*
	 * Grow the in-inode space.
	 */
	xfs_idata_realloc(dp, xfs_dir2_sf_entsize_byname(sfp, args->namelen),
		XFS_DATA_FORK);
	/*
	 * Need to set up again due to realloc of the inode data.
	 */
	sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
	sfep = (xfs_dir2_sf_entry_t *)((char *)sfp + byteoff);
	/*
	 * Fill in the new entry.
	 */
	sfep->namelen = args->namelen;
	xfs_dir2_sf_put_offset(sfep, offset);
	memcpy(sfep->name, args->name, sfep->namelen);
	xfs_dir2_sf_put_inumber(sfp, &args->inumber,
		xfs_dir2_sf_inumberp(sfep));
	/*
	 * Update the header and inode.
	 */
	sfp->hdr.count++;
#if XFS_BIG_INUMS
	if (args->inumber > XFS_DIR2_MAX_SHORT_INUM)
		sfp->hdr.i8count++;
#endif
	dp->i_d.di_size = new_isize;
	xfs_dir2_sf_check(args);
}