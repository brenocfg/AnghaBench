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
typedef  int processorid_t ;
typedef  int /*<<< orphan*/  maxid ;
struct TYPE_4__ {int (* dtv_status ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ dtrace_vector_t ;
struct TYPE_5__ {int /*<<< orphan*/  dt_varg; TYPE_1__* dt_vector; } ;
typedef  TYPE_2__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  P_STATUS ; 
 int p_online (int,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dt_status(dtrace_hdl_t *dtp, processorid_t cpu)
{
	const dtrace_vector_t *v = dtp->dt_vector;

	if (v == NULL) {
#ifdef illumos
		return (p_online(cpu, P_STATUS));
#else
		int maxid = 0;
		size_t len = sizeof(maxid);
		if (sysctlbyname("kern.smp.maxid", &maxid, &len, NULL, 0) != 0)
			return (cpu == 0 ? 1 : -1);
		else
			return (cpu <= maxid ? 1 : -1);
#endif
	}

	return (v->dtv_status(dtp->dt_varg, cpu));
}