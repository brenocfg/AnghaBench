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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ object; int /*<<< orphan*/  sema; } ;
typedef  TYPE_2__ sema_st ;
typedef  int /*<<< orphan*/  sem_t ;
typedef  int s32 ;

/* Variables and functions */
 TYPE_2__* __lwp_sema_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_sema_surrender (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 

s32 LWP_SemPost(sem_t sem)
{
	sema_st *lwp_sem = __lwp_sema_open(sem);
	if(!lwp_sem) return -1;

	__lwp_sema_surrender(&lwp_sem->sema,lwp_sem->object.id);
	__lwp_thread_dispatchenable();

	return 0;
}