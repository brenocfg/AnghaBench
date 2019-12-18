#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  t_mountp; } ;
typedef  TYPE_4__ xfs_trans_t ;
struct TYPE_20__ {int di_mode; scalar_t__ di_format; } ;
struct TYPE_22__ {TYPE_3__ i_d; TYPE_2__* i_mount; } ;
typedef  TYPE_5__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_ino_t ;
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_extlen_t ;
struct TYPE_23__ {int op_flags; TYPE_4__* trans; int /*<<< orphan*/  whichfork; int /*<<< orphan*/  total; int /*<<< orphan*/ * flist; int /*<<< orphan*/ * firstblock; TYPE_5__* dp; int /*<<< orphan*/  inumber; int /*<<< orphan*/  hashval; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ xfs_da_args_t ;
typedef  int /*<<< orphan*/  xfs_bmap_free_t ;
struct xfs_name {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_19__ {TYPE_1__* m_dirnameops; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* hashname ) (struct xfs_name*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_DA_OP_ADDNAME ; 
 int XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct xfs_name*) ; 
 int xfs_dir2_block_addname (TYPE_6__*) ; 
 int xfs_dir2_isblock (TYPE_4__*,TYPE_5__*,int*) ; 
 int xfs_dir2_isleaf (TYPE_4__*,TYPE_5__*,int*) ; 
 int xfs_dir2_leaf_addname (TYPE_6__*) ; 
 int xfs_dir2_node_addname (TYPE_6__*) ; 
 int xfs_dir2_sf_addname (TYPE_6__*) ; 
 int xfs_dir_ino_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_dir_create ; 

int
xfs_dir_createname(
	xfs_trans_t		*tp,
	xfs_inode_t		*dp,
	struct xfs_name		*name,
	xfs_ino_t		inum,		/* new entry inode number */
	xfs_fsblock_t		*first,		/* bmap's firstblock */
	xfs_bmap_free_t		*flist,		/* bmap's freeblock list */
	xfs_extlen_t		total)		/* bmap's total block count */
{
	xfs_da_args_t		args;
	int			rval;
	int			v;		/* type-checking value */

	ASSERT((dp->i_d.di_mode & S_IFMT) == S_IFDIR);
	if ((rval = xfs_dir_ino_validate(tp->t_mountp, inum)))
		return rval;
	XFS_STATS_INC(xs_dir_create);

	memset(&args, 0, sizeof(xfs_da_args_t));
	args.name = name->name;
	args.namelen = name->len;
	args.hashval = dp->i_mount->m_dirnameops->hashname(name);
	args.inumber = inum;
	args.dp = dp;
	args.firstblock = first;
	args.flist = flist;
	args.total = total;
	args.whichfork = XFS_DATA_FORK;
	args.trans = tp;
	args.op_flags = XFS_DA_OP_ADDNAME | XFS_DA_OP_OKNOENT;

	if (dp->i_d.di_format == XFS_DINODE_FMT_LOCAL)
		rval = xfs_dir2_sf_addname(&args);
	else if ((rval = xfs_dir2_isblock(tp, dp, &v)))
		return rval;
	else if (v)
		rval = xfs_dir2_block_addname(&args);
	else if ((rval = xfs_dir2_isleaf(tp, dp, &v)))
		return rval;
	else if (v)
		rval = xfs_dir2_leaf_addname(&args);
	else
		rval = xfs_dir2_node_addname(&args);
	return rval;
}