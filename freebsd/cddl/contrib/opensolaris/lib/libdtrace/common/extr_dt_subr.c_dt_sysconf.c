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
struct TYPE_4__ {long (* dtv_sysconf ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ dtrace_vector_t ;
struct TYPE_5__ {int /*<<< orphan*/  dt_varg; TYPE_1__* dt_vector; } ;
typedef  TYPE_2__ dtrace_hdl_t ;

/* Variables and functions */
 long stub1 (int /*<<< orphan*/ ,int) ; 
 long sysconf (int) ; 

long
dt_sysconf(dtrace_hdl_t *dtp, int name)
{
	const dtrace_vector_t *v = dtp->dt_vector;

	if (v == NULL)
		return (sysconf(name));

	return (v->dtv_sysconf(dtp->dt_varg, name));
}