#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_7__ {int /*<<< orphan*/  dt_nprovs; TYPE_2__** dt_provs; int /*<<< orphan*/  dt_provlist; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_8__ {struct TYPE_8__* pv_next; } ;
typedef  TYPE_2__ dt_provider_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_list_append (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static dt_provider_t *
dt_provider_insert(dtrace_hdl_t *dtp, dt_provider_t *pvp, uint_t h)
{
	dt_list_append(&dtp->dt_provlist, pvp);

	pvp->pv_next = dtp->dt_provs[h];
	dtp->dt_provs[h] = pvp;
	dtp->dt_nprovs++;

	return (pvp);
}