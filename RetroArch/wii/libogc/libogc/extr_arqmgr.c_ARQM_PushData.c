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
typedef  int u32 ;
typedef  scalar_t__ s32 ;
struct TYPE_3__ {scalar_t__ polled; int aram_start; int /*<<< orphan*/  arqhandle; } ;
typedef  TYPE_1__ ARQM_Info ;

/* Variables and functions */
 int ARQM_STACKENTRIES ; 
 int /*<<< orphan*/  ARQ_MRAMTOARAM ; 
 int /*<<< orphan*/  ARQ_PRIO_HI ; 
 int /*<<< orphan*/  ARQ_PostRequestAsync (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int ROUNDUP32 (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int __ARQMFreeBytes ; 
 TYPE_1__* __ARQMInfo ; 
 int /*<<< orphan*/  __ARQMPollCallback ; 
 int __ARQMStackLocation ; 
 int* __ARQMStackPointer ; 

u32 ARQM_PushData(void *buffer,s32 len)
{
	u32 rlen,level;
	ARQM_Info *ptr;

	if(((u32)buffer)&0x1f || len<=0) return 0;

	rlen = ROUNDUP32(len);
	if(__ARQMFreeBytes>=rlen && __ARQMStackLocation<(ARQM_STACKENTRIES-1)) {
		ptr = &__ARQMInfo[__ARQMStackLocation];

		_CPU_ISR_Disable(level);
		ptr->polled = FALSE;
		ptr->aram_start = __ARQMStackPointer[__ARQMStackLocation++];
		__ARQMStackPointer[__ARQMStackLocation] = ptr->aram_start+rlen;
		__ARQMFreeBytes -= rlen;

		ARQ_PostRequestAsync(&ptr->arqhandle,__ARQMStackLocation-1,ARQ_MRAMTOARAM,ARQ_PRIO_HI,ptr->aram_start,(u32)buffer,rlen,__ARQMPollCallback);
		_CPU_ISR_Restore(level);

		while(ptr->polled==FALSE);
		return (ptr->aram_start);
	}
	return 0;
}