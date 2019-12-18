#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_16__ {int di_mode; scalar_t__ di_format; } ;
struct TYPE_17__ {TYPE_3__ i_d; TYPE_2__* i_mount; } ;
typedef  TYPE_4__ xfs_inode_t ;
struct TYPE_18__ {int op_flags; int /*<<< orphan*/ * trans; int /*<<< orphan*/  whichfork; TYPE_4__* dp; int /*<<< orphan*/  hashval; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ xfs_da_args_t ;
typedef  scalar_t__ uint ;
struct xfs_name {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {TYPE_1__* m_dirnameops; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* hashname ) (struct xfs_name*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_DA_OP_ADDNAME ; 
 int XFS_DA_OP_JUSTCHECK ; 
 int XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct xfs_name*) ; 
 int xfs_dir2_block_addname (TYPE_5__*) ; 
 int xfs_dir2_isblock (int /*<<< orphan*/ *,TYPE_4__*,int*) ; 
 int xfs_dir2_isleaf (int /*<<< orphan*/ *,TYPE_4__*,int*) ; 
 int xfs_dir2_leaf_addname (TYPE_5__*) ; 
 int xfs_dir2_node_addname (TYPE_5__*) ; 
 int xfs_dir2_sf_addname (TYPE_5__*) ; 

int
xfs_dir_canenter(
	xfs_trans_t	*tp,
	xfs_inode_t	*dp,
	struct xfs_name	*name,		/* name of entry to add */
	uint		resblks)
{
	xfs_da_args_t	args;
	int		rval;
	int		v;		/* type-checking value */

	if (resblks)
		return 0;

	ASSERT((dp->i_d.di_mode & S_IFMT) == S_IFDIR);

	memset(&args, 0, sizeof(xfs_da_args_t));
	args.name = name->name;
	args.namelen = name->len;
	args.hashval = dp->i_mount->m_dirnameops->hashname(name);
	args.dp = dp;
	args.whichfork = XFS_DATA_FORK;
	args.trans = tp;
	args.op_flags = XFS_DA_OP_JUSTCHECK | XFS_DA_OP_ADDNAME |
							XFS_DA_OP_OKNOENT;

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