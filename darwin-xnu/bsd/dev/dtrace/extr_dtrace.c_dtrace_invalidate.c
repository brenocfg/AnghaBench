#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* dtps_enable ) (void*,dtrace_id_t,void*) ;} ;
struct TYPE_4__ {int dtpv_defunct; TYPE_1__ dtpv_pops; } ;
typedef  TYPE_2__ dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ dtrace_enable_nullop ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
dtrace_invalidate(dtrace_provider_id_t id)
{
	dtrace_provider_t *pvp = (dtrace_provider_t *)id;

	ASSERT(pvp->dtpv_pops.dtps_enable !=
	    (int (*)(void *, dtrace_id_t, void *))dtrace_enable_nullop);

	lck_mtx_lock(&dtrace_provider_lock);
	lck_mtx_lock(&dtrace_lock);

	pvp->dtpv_defunct = 1;

	lck_mtx_unlock(&dtrace_lock);
	lck_mtx_unlock(&dtrace_provider_lock);
}