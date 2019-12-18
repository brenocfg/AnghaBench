#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* cpu_mtypes; } ;
typedef  TYPE_1__ mtypes_cpu_t ;
typedef  int /*<<< orphan*/  mtc ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {scalar_t__* m_mtypes; } ;
struct TYPE_6__ {TYPE_1__* mbs_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int MT_MAX ; 
 int /*<<< orphan*/  bcopy (scalar_t__**,scalar_t__**,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 TYPE_3__ mbstat ; 
 int /*<<< orphan*/  mbuf_mlock ; 
 TYPE_2__* mbuf_mtypes ; 
 int ncpu ; 

__attribute__((used)) static void
mbuf_mtypes_sync(boolean_t locked)
{
	int m, n;
	mtypes_cpu_t mtc;

	if (locked)
		LCK_MTX_ASSERT(mbuf_mlock, LCK_MTX_ASSERT_OWNED);

	bzero(&mtc, sizeof (mtc));
	for (m = 0; m < ncpu; m++) {
		mtypes_cpu_t *scp = &mbuf_mtypes->mbs_cpu[m];
		mtypes_cpu_t temp;

		bcopy(&scp->cpu_mtypes, &temp.cpu_mtypes,
		    sizeof (temp.cpu_mtypes));

		for (n = 0; n < MT_MAX; n++)
			mtc.cpu_mtypes[n] += temp.cpu_mtypes[n];
	}
	if (!locked)
		lck_mtx_lock(mbuf_mlock);
	for (n = 0; n < MT_MAX; n++)
		mbstat.m_mtypes[n] = mtc.cpu_mtypes[n];
	if (!locked)
		lck_mtx_unlock(mbuf_mlock);
}