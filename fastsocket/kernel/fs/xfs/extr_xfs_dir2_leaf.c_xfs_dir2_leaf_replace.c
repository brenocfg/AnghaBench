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
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_18__ {int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct TYPE_19__ {TYPE_3__* ents; } ;
typedef  TYPE_2__ xfs_dir2_leaf_t ;
struct TYPE_20__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_3__ xfs_dir2_leaf_entry_t ;
struct TYPE_21__ {int /*<<< orphan*/  inumber; } ;
typedef  TYPE_4__ xfs_dir2_data_entry_t ;
struct TYPE_22__ {TYPE_2__* data; } ;
typedef  TYPE_5__ xfs_dabuf_t ;
struct TYPE_23__ {scalar_t__ inumber; int /*<<< orphan*/ * trans; TYPE_1__* dp; } ;
typedef  TYPE_6__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leaf_replace (TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_da_brelse (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_check (TYPE_1__*,TYPE_5__*) ; 
 int xfs_dir2_leaf_lookup_int (TYPE_6__*,TYPE_5__**,int*,TYPE_5__**) ; 

int						/* error */
xfs_dir2_leaf_replace(
	xfs_da_args_t		*args)		/* operation arguments */
{
	xfs_dabuf_t		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	int			index;		/* index of leaf entry */
	xfs_dabuf_t		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_trans_t		*tp;		/* transaction pointer */

	trace_xfs_dir2_leaf_replace(args);

	/*
	 * Look up the entry.
	 */
	if ((error = xfs_dir2_leaf_lookup_int(args, &lbp, &index, &dbp))) {
		return error;
	}
	dp = args->dp;
	leaf = lbp->data;
	/*
	 * Point to the leaf entry, get data address from it.
	 */
	lep = &leaf->ents[index];
	/*
	 * Point to the data entry.
	 */
	dep = (xfs_dir2_data_entry_t *)
	      ((char *)dbp->data +
	       xfs_dir2_dataptr_to_off(dp->i_mount, be32_to_cpu(lep->address)));
	ASSERT(args->inumber != be64_to_cpu(dep->inumber));
	/*
	 * Put the new inode number in, log it.
	 */
	dep->inumber = cpu_to_be64(args->inumber);
	tp = args->trans;
	xfs_dir2_data_log_entry(tp, dbp, dep);
	xfs_da_buf_done(dbp);
	xfs_dir2_leaf_check(dp, lbp);
	xfs_da_brelse(tp, lbp);
	return 0;
}