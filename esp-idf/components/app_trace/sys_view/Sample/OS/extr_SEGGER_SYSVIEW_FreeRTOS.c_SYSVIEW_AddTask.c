#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* U32 ;
struct TYPE_2__ {scalar_t__ xHandle; char const* pcTaskName; unsigned int uxCurrentPriority; unsigned int uStackHighWaterMark; void* pxStack; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEGGER_SYSVIEW_Warn (char*) ; 
 unsigned int SYSVIEW_FREERTOS_MAX_NOF_TASKS ; 
 int /*<<< orphan*/  SYSVIEW_SendTaskInfo (void*,char const*,unsigned int,void*,unsigned int) ; 
 TYPE_1__* _aTasks ; 
 scalar_t__ memcmp (char const*,char*,int) ; 

void SYSVIEW_AddTask(U32 xHandle, const char* pcTaskName, unsigned uxCurrentPriority, U32  pxStack, unsigned uStackHighWaterMark) {
  unsigned n;
  
  if (memcmp(pcTaskName, "IDLE", 5) == 0) {
    return;
  }
  
  for (n = 0; n < SYSVIEW_FREERTOS_MAX_NOF_TASKS; n++) {
    if (_aTasks[n].xHandle == 0) {
      break;
    }
  }
  if (n == SYSVIEW_FREERTOS_MAX_NOF_TASKS) {
    SEGGER_SYSVIEW_Warn("SYSTEMVIEW: Could not record task information. Maximum number of tasks reached.");
    return;
  }

  _aTasks[n].xHandle = xHandle;
  _aTasks[n].pcTaskName = pcTaskName;
  _aTasks[n].uxCurrentPriority = uxCurrentPriority;
  _aTasks[n].pxStack = pxStack;
  _aTasks[n].uStackHighWaterMark = uStackHighWaterMark;

  SYSVIEW_SendTaskInfo(xHandle, pcTaskName,uxCurrentPriority, pxStack, uStackHighWaterMark);

}