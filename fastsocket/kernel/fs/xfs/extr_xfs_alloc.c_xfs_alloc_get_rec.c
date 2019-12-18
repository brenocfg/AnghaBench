#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* xfs_extlen_t ;
typedef  void* xfs_agblock_t ;
struct TYPE_2__ {int /*<<< orphan*/  ar_blockcount; int /*<<< orphan*/  ar_startblock; } ;
union xfs_btree_rec {TYPE_1__ alloc; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int xfs_btree_get_rec (struct xfs_btree_cur*,union xfs_btree_rec**,int*) ; 

int					/* error */
xfs_alloc_get_rec(
	struct xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		*bno,	/* output: starting block of extent */
	xfs_extlen_t		*len,	/* output: length of extent */
	int			*stat)	/* output: success/failure */
{
	union xfs_btree_rec	*rec;
	int			error;

	error = xfs_btree_get_rec(cur, &rec, stat);
	if (!error && *stat == 1) {
		*bno = be32_to_cpu(rec->alloc.ar_startblock);
		*len = be32_to_cpu(rec->alloc.ar_blockcount);
	}
	return error;
}