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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  TaskHandle_t ;
struct TYPE_2__ {scalar_t__ uStackHighWaterMark; scalar_t__ pxStack; scalar_t__ uxCurrentPriority; int /*<<< orphan*/  pcTaskName; scalar_t__ xHandle; } ;

/* Variables and functions */
 unsigned int SYSVIEW_FREERTOS_MAX_NOF_TASKS ; 
 int /*<<< orphan*/  SYSVIEW_SendTaskInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* _aTasks ; 
 scalar_t__ uxTaskGetStackHighWaterMark (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _cbSendTaskList(void) {
  unsigned n;

  for (n = 0; n < SYSVIEW_FREERTOS_MAX_NOF_TASKS; n++) {
    if (_aTasks[n].xHandle) {
#if INCLUDE_uxTaskGetStackHighWaterMark // Report Task Stack High Watermark
      _aTasks[n].uStackHighWaterMark = uxTaskGetStackHighWaterMark((TaskHandle_t)_aTasks[n].xHandle);
#endif
      SYSVIEW_SendTaskInfo((U32)_aTasks[n].xHandle, _aTasks[n].pcTaskName, (unsigned)_aTasks[n].uxCurrentPriority, (U32)_aTasks[n].pxStack, (unsigned)_aTasks[n].uStackHighWaterMark);
    }
  }
}