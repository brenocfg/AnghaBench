#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pv_probes; int /*<<< orphan*/  pv_flags; } ;
typedef  TYPE_1__ dt_provider_t ;
struct TYPE_7__ {scalar_t__ pr_xargs; scalar_t__ pr_nargs; TYPE_5__* pr_ident; TYPE_1__* pr_pvp; } ;
typedef  TYPE_2__ dt_probe_t ;
struct TYPE_8__ {scalar_t__ di_kind; TYPE_2__* di_data; } ;

/* Variables and functions */
 scalar_t__ DT_IDENT_PROBE ; 
 int /*<<< orphan*/  DT_PROVIDER_INTF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_idhash_xinsert (int /*<<< orphan*/ ,TYPE_5__*) ; 

void
dt_probe_declare(dt_provider_t *pvp, dt_probe_t *prp)
{
	assert(prp->pr_ident->di_kind == DT_IDENT_PROBE);
	assert(prp->pr_ident->di_data == prp);
	assert(prp->pr_pvp == NULL);

	if (prp->pr_xargs != prp->pr_nargs)
		pvp->pv_flags &= ~DT_PROVIDER_INTF;

	prp->pr_pvp = pvp;
	dt_idhash_xinsert(pvp->pv_probes, prp->pr_ident);
}