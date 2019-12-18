#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ps_prochandle {int dummy; } ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_3__ {int dpr_stop; int /*<<< orphan*/  dpr_lock; int /*<<< orphan*/  dpr_cv; } ;
typedef  TYPE_1__ dt_proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int DT_PROC_STOP_IDLE ; 
 TYPE_1__* dt_proc_lookup (int /*<<< orphan*/ *,struct ps_prochandle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void
dt_proc_continue(dtrace_hdl_t *dtp, struct ps_prochandle *P)
{
	dt_proc_t *dpr = dt_proc_lookup(dtp, P, B_FALSE);

	(void) pthread_mutex_lock(&dpr->dpr_lock);

	if (dpr->dpr_stop & DT_PROC_STOP_IDLE) {
		dpr->dpr_stop &= ~DT_PROC_STOP_IDLE;
		(void) pthread_cond_broadcast(&dpr->dpr_cv);
	}

	(void) pthread_mutex_unlock(&dpr->dpr_lock);
}