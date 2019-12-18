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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lwp_semattr ;
struct TYPE_3__ {int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  count; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ lwp_sema ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_SEMA_TIMEOUT ; 
 int /*<<< orphan*/  LWP_STATES_WAITING_FOR_SEMAPHORE ; 
 int /*<<< orphan*/  LWP_THREADQ_MODEFIFO ; 
 int /*<<< orphan*/  LWP_THREADQ_MODEPRIORITY ; 
 scalar_t__ __lwp_sema_ispriority (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_threadqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __lwp_sema_initialize(lwp_sema *sema,lwp_semattr *attrs,u32 init_count)
{
	sema->attrs = *attrs;
	sema->count = init_count;

	__lwp_threadqueue_init(&sema->wait_queue,__lwp_sema_ispriority(attrs)?LWP_THREADQ_MODEPRIORITY:LWP_THREADQ_MODEFIFO,LWP_STATES_WAITING_FOR_SEMAPHORE,LWP_SEMA_TIMEOUT);
}