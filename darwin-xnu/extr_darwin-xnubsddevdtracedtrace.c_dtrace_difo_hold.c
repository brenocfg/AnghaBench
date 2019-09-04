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
typedef  size_t uint_t ;
struct TYPE_4__ {scalar_t__ dtdv_id; } ;
typedef  TYPE_1__ dtrace_difv_t ;
struct TYPE_5__ {scalar_t__ dtdo_refcnt; size_t dtdo_varlen; TYPE_1__* dtdo_vartab; } ;
typedef  TYPE_2__ dtrace_difo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DIF_VAR_VTIMESTAMP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_vtime_enable () ; 
 int /*<<< orphan*/  dtrace_vtime_references ; 

__attribute__((used)) static void
dtrace_difo_hold(dtrace_difo_t *dp)
{
	uint_t i;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	dp->dtdo_refcnt++;
	ASSERT(dp->dtdo_refcnt != 0);

	/*
	 * We need to check this DIF object for references to the variable
	 * DIF_VAR_VTIMESTAMP.
	 */
	for (i = 0; i < dp->dtdo_varlen; i++) {
		dtrace_difv_t *v = &dp->dtdo_vartab[i];

		if (v->dtdv_id != DIF_VAR_VTIMESTAMP)
			continue;

		if (dtrace_vtime_references++ == 0)
			dtrace_vtime_enable();
	}
}