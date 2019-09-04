#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_6__ {scalar_t__ dtp_refcnt; TYPE_2__* dtp_difo; } ;
typedef  TYPE_1__ dtrace_predicate_t ;
struct TYPE_7__ {scalar_t__ dtdo_refcnt; } ;
typedef  TYPE_2__ dtrace_difo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_difo_release (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 

__attribute__((used)) static void
dtrace_predicate_release(dtrace_predicate_t *pred, dtrace_vstate_t *vstate)
{
	dtrace_difo_t *dp = pred->dtp_difo;
#pragma unused(dp) /* __APPLE__ */

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);
	ASSERT(dp != NULL && dp->dtdo_refcnt != 0);
	ASSERT(pred->dtp_refcnt > 0);

	if (--pred->dtp_refcnt == 0) {
		dtrace_difo_release(pred->dtp_difo, vstate);
		kmem_free(pred, sizeof (dtrace_predicate_t));
	}
}