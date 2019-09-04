#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dofhp_dof; } ;
struct TYPE_6__ {scalar_t__ dthp_ref; TYPE_1__ dthp_prov; } ;
typedef  TYPE_2__ dtrace_helper_provider_t ;
typedef  int /*<<< orphan*/  dof_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_dof_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_helper_provider_destroy(dtrace_helper_provider_t *hprov)
{
	lck_mtx_lock(&dtrace_lock);

	if (--hprov->dthp_ref == 0) {
		dof_hdr_t *dof;
		lck_mtx_unlock(&dtrace_lock);
		dof = (dof_hdr_t *)(uintptr_t)hprov->dthp_prov.dofhp_dof;
		dtrace_dof_destroy(dof);
		kmem_free(hprov, sizeof (dtrace_helper_provider_t));
	} else {
		lck_mtx_unlock(&dtrace_lock);
	}
}