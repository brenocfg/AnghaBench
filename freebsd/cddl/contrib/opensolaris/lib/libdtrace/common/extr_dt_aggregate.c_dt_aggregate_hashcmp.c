#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dtagd_nrecs; } ;
typedef  TYPE_2__ dtrace_aggdesc_t ;
struct TYPE_4__ {TYPE_2__* dtada_desc; } ;
struct TYPE_6__ {TYPE_1__ dtahe_data; } ;
typedef  TYPE_3__ dt_ahashent_t ;

/* Variables and functions */
 int DT_GREATERTHAN ; 
 int DT_LESSTHAN ; 

__attribute__((used)) static int
dt_aggregate_hashcmp(const void *lhs, const void *rhs)
{
	dt_ahashent_t *lh = *((dt_ahashent_t **)lhs);
	dt_ahashent_t *rh = *((dt_ahashent_t **)rhs);
	dtrace_aggdesc_t *lagg = lh->dtahe_data.dtada_desc;
	dtrace_aggdesc_t *ragg = rh->dtahe_data.dtada_desc;

	if (lagg->dtagd_nrecs < ragg->dtagd_nrecs)
		return (DT_LESSTHAN);

	if (lagg->dtagd_nrecs > ragg->dtagd_nrecs)
		return (DT_GREATERTHAN);

	return (0);
}