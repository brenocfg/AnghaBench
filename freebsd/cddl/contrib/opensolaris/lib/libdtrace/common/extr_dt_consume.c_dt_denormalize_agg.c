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
typedef  scalar_t__ dtrace_aggvarid_t ;
struct TYPE_4__ {scalar_t__ dtagd_nrecs; scalar_t__ dtagd_varid; } ;
typedef  TYPE_1__ dtrace_aggdesc_t ;
struct TYPE_5__ {TYPE_1__* dtada_desc; } ;
typedef  TYPE_2__ dtrace_aggdata_t ;

/* Variables and functions */
 int DTRACE_AGGWALK_DENORMALIZE ; 
 int DTRACE_AGGWALK_NEXT ; 

__attribute__((used)) static int
dt_denormalize_agg(const dtrace_aggdata_t *aggdata, void *arg)
{
	dtrace_aggdesc_t *agg = aggdata->dtada_desc;
	dtrace_aggvarid_t id = *((dtrace_aggvarid_t *)arg);

	if (agg->dtagd_nrecs == 0)
		return (DTRACE_AGGWALK_NEXT);

	if (agg->dtagd_varid != id)
		return (DTRACE_AGGWALK_NEXT);

	return (DTRACE_AGGWALK_DENORMALIZE);
}