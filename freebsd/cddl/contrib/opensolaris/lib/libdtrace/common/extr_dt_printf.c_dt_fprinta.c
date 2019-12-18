#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dtrace_recdesc_t ;
struct TYPE_10__ {int dt_errno; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_11__ {int /*<<< orphan*/  dtagd_flags; int /*<<< orphan*/  dtagd_nrecs; int /*<<< orphan*/ * dtagd_rec; } ;
typedef  TYPE_2__ dtrace_aggdesc_t ;
struct TYPE_12__ {int /*<<< orphan*/  dtada_size; int /*<<< orphan*/  dtada_data; TYPE_2__* dtada_desc; } ;
typedef  TYPE_3__ dtrace_aggdata_t ;
struct TYPE_13__ {int pfw_aid; int pfw_err; TYPE_7__* pfw_argv; int /*<<< orphan*/  pfw_fp; } ;
typedef  TYPE_4__ dt_pfwalk_t ;
struct TYPE_14__ {TYPE_1__* pfv_dtp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_AGD_PRINTED ; 
 int dt_printf_format (TYPE_1__*,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__ const**,int) ; 
 scalar_t__ dt_printf_getint (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
dt_fprinta(const dtrace_aggdata_t *adp, void *arg)
{
	const dtrace_aggdesc_t *agg = adp->dtada_desc;
	const dtrace_recdesc_t *recp = &agg->dtagd_rec[0];
	uint_t nrecs = agg->dtagd_nrecs;
	dt_pfwalk_t *pfw = arg;
	dtrace_hdl_t *dtp = pfw->pfw_argv->pfv_dtp;
	int id;

	if (dt_printf_getint(dtp, recp++, nrecs--,
	    adp->dtada_data, adp->dtada_size, &id) != 0 || pfw->pfw_aid != id)
		return (0); /* no aggregation id or id does not match */

	if (dt_printf_format(dtp, pfw->pfw_fp, pfw->pfw_argv,
	    recp, nrecs, adp->dtada_data, adp->dtada_size, &adp, 1) == -1)
		return (pfw->pfw_err = dtp->dt_errno);

	/*
	 * Cast away the const to set the bit indicating that this aggregation
	 * has been printed.
	 */
	((dtrace_aggdesc_t *)agg)->dtagd_flags |= DTRACE_AGD_PRINTED;

	return (0);
}