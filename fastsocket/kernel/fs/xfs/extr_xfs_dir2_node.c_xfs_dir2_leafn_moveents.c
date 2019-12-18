#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_17__ {int count; int stale; } ;
struct TYPE_18__ {TYPE_1__ hdr; TYPE_12__* ents; } ;
typedef  TYPE_2__ xfs_dir2_leaf_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_entry_t ;
struct TYPE_19__ {TYPE_2__* data; } ;
typedef  TYPE_3__ xfs_dabuf_t ;
struct TYPE_20__ {int /*<<< orphan*/  dp; int /*<<< orphan*/ * trans; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct TYPE_16__ {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 scalar_t__ XFS_DIR2_NULL_DATAPTR ; 
 int /*<<< orphan*/  be16_add_cpu (int*,int) ; 
 int be16_to_cpu (int) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_12__*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  memmove (TYPE_12__*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leafn_moveents (TYPE_4__*,int,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_ents (int /*<<< orphan*/ *,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_header (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_dir2_leafn_check (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
xfs_dir2_leafn_moveents(
	xfs_da_args_t	*args,			/* operation arguments */
	xfs_dabuf_t	*bp_s,			/* source leaf buffer */
	int		start_s,		/* source leaf index */
	xfs_dabuf_t	*bp_d,			/* destination leaf buffer */
	int		start_d,		/* destination leaf index */
	int		count)			/* count of leaves to copy */
{
	xfs_dir2_leaf_t	*leaf_d;		/* destination leaf structure */
	xfs_dir2_leaf_t	*leaf_s;		/* source leaf structure */
	int		stale;			/* count stale leaves copied */
	xfs_trans_t	*tp;			/* transaction pointer */

	trace_xfs_dir2_leafn_moveents(args, start_s, start_d, count);

	/*
	 * Silently return if nothing to do.
	 */
	if (count == 0) {
		return;
	}
	tp = args->trans;
	leaf_s = bp_s->data;
	leaf_d = bp_d->data;
	/*
	 * If the destination index is not the end of the current
	 * destination leaf entries, open up a hole in the destination
	 * to hold the new entries.
	 */
	if (start_d < be16_to_cpu(leaf_d->hdr.count)) {
		memmove(&leaf_d->ents[start_d + count], &leaf_d->ents[start_d],
			(be16_to_cpu(leaf_d->hdr.count) - start_d) *
			sizeof(xfs_dir2_leaf_entry_t));
		xfs_dir2_leaf_log_ents(tp, bp_d, start_d + count,
			count + be16_to_cpu(leaf_d->hdr.count) - 1);
	}
	/*
	 * If the source has stale leaves, count the ones in the copy range
	 * so we can update the header correctly.
	 */
	if (leaf_s->hdr.stale) {
		int	i;			/* temp leaf index */

		for (i = start_s, stale = 0; i < start_s + count; i++) {
			if (be32_to_cpu(leaf_s->ents[i].address) == XFS_DIR2_NULL_DATAPTR)
				stale++;
		}
	} else
		stale = 0;
	/*
	 * Copy the leaf entries from source to destination.
	 */
	memcpy(&leaf_d->ents[start_d], &leaf_s->ents[start_s],
		count * sizeof(xfs_dir2_leaf_entry_t));
	xfs_dir2_leaf_log_ents(tp, bp_d, start_d, start_d + count - 1);
	/*
	 * If there are source entries after the ones we copied,
	 * delete the ones we copied by sliding the next ones down.
	 */
	if (start_s + count < be16_to_cpu(leaf_s->hdr.count)) {
		memmove(&leaf_s->ents[start_s], &leaf_s->ents[start_s + count],
			count * sizeof(xfs_dir2_leaf_entry_t));
		xfs_dir2_leaf_log_ents(tp, bp_s, start_s, start_s + count - 1);
	}
	/*
	 * Update the headers and log them.
	 */
	be16_add_cpu(&leaf_s->hdr.count, -(count));
	be16_add_cpu(&leaf_s->hdr.stale, -(stale));
	be16_add_cpu(&leaf_d->hdr.count, count);
	be16_add_cpu(&leaf_d->hdr.stale, stale);
	xfs_dir2_leaf_log_header(tp, bp_s);
	xfs_dir2_leaf_log_header(tp, bp_d);
	xfs_dir2_leafn_check(args->dp, bp_s);
	xfs_dir2_leafn_check(args->dp, bp_d);
}