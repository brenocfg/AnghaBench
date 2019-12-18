#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* buf_t ;
struct TYPE_8__ {int /*<<< orphan*/  bufs_eblk; } ;
struct TYPE_7__ {int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int BQ_EMPTY ; 
 int B_INVAL ; 
 int B_META ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  allocbuf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binshash (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_mtxp ; 
 TYPE_3__ bufstats ; 
 TYPE_1__* getnewbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  invalhash ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

buf_t
buf_geteblk(int size)
{
	buf_t	bp = NULL;
	int queue = BQ_EMPTY;

	do {
		lck_mtx_lock_spin(buf_mtxp);

		bp = getnewbuf(0, 0, &queue);
	} while (bp == NULL);

	SET(bp->b_flags, (B_META|B_INVAL));

#if DIAGNOSTIC
	assert(queue == BQ_EMPTY);
#endif /* DIAGNOSTIC */
	/* XXX need to implement logic to deal with other queues */

	binshash(bp, &invalhash);
	bufstats.bufs_eblk++;

	lck_mtx_unlock(buf_mtxp);

	allocbuf(bp, size);

	return (bp);
}