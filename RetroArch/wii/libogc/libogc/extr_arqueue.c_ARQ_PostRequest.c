#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ ARQRequest ;

/* Variables and functions */
 int /*<<< orphan*/  ARQ_PostRequestAsync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ARQ_TASK_FINISHED ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ARQCallbackSync ; 
 int /*<<< orphan*/  __ARQSyncQueue ; 

void ARQ_PostRequest(ARQRequest *req,u32 owner,u32 dir,u32 prio,u32 aram_addr,u32 mram_addr,u32 len)
{
	u32 level;

	ARQ_PostRequestAsync(req,owner,dir,prio,aram_addr,mram_addr,len,__ARQCallbackSync);

	_CPU_ISR_Disable(level);
	while(req->state!=ARQ_TASK_FINISHED) {
		LWP_ThreadSleep(__ARQSyncQueue);
	}
	_CPU_ISR_Restore(level);
}