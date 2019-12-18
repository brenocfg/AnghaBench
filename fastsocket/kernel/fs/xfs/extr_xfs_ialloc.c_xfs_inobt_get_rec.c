#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ir_free; void* ir_freecount; void* ir_startino; } ;
typedef  TYPE_2__ xfs_inobt_rec_incore_t ;
struct TYPE_4__ {int /*<<< orphan*/  ir_free; int /*<<< orphan*/  ir_freecount; int /*<<< orphan*/  ir_startino; } ;
union xfs_btree_rec {TYPE_1__ inobt; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int xfs_btree_get_rec (struct xfs_btree_cur*,union xfs_btree_rec**,int*) ; 

int					/* error */
xfs_inobt_get_rec(
	struct xfs_btree_cur	*cur,	/* btree cursor */
	xfs_inobt_rec_incore_t	*irec,	/* btree record */
	int			*stat)	/* output: success/failure */
{
	union xfs_btree_rec	*rec;
	int			error;

	error = xfs_btree_get_rec(cur, &rec, stat);
	if (!error && *stat == 1) {
		irec->ir_startino = be32_to_cpu(rec->inobt.ir_startino);
		irec->ir_freecount = be32_to_cpu(rec->inobt.ir_freecount);
		irec->ir_free = be64_to_cpu(rec->inobt.ir_free);
	}
	return error;
}