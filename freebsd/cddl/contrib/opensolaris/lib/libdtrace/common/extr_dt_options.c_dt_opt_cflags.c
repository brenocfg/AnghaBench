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
struct TYPE_6__ {uintptr_t dt_cflags; TYPE_1__* dt_pcb; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_5__ {uintptr_t pcb_cflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_opt_cflags(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	if (arg != NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	if (dtp->dt_pcb != NULL)
		dtp->dt_pcb->pcb_cflags |= option;
	else
		dtp->dt_cflags |= option;

	return (0);
}