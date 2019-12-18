#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int dpr_stop; int /*<<< orphan*/  dpr_lock; int /*<<< orphan*/  dpr_cv; } ;
typedef  TYPE_1__ dt_proc_t ;

/* Variables and functions */
 int DT_MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int DT_PROC_STOP_IDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_proc_bpdisable (TYPE_1__*) ; 
 int /*<<< orphan*/  dt_proc_bpenable (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dt_proc_stop(dt_proc_t *dpr, uint8_t why)
{
	assert(DT_MUTEX_HELD(&dpr->dpr_lock));
	assert(why != DT_PROC_STOP_IDLE);

	if (dpr->dpr_stop & why) {
		dpr->dpr_stop |= DT_PROC_STOP_IDLE;
		dpr->dpr_stop &= ~why;

		(void) pthread_cond_broadcast(&dpr->dpr_cv);

		/*
		 * We disable breakpoints while stopped to preserve the
		 * integrity of the program text for both our own disassembly
		 * and that of the kernel.
		 */
		dt_proc_bpdisable(dpr);

		while (dpr->dpr_stop & DT_PROC_STOP_IDLE)
			(void) pthread_cond_wait(&dpr->dpr_cv, &dpr->dpr_lock);

		dt_proc_bpenable(dpr);
	}
}