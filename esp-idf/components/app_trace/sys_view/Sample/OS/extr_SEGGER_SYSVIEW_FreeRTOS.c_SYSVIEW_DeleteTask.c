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
typedef  scalar_t__ U32 ;
struct TYPE_2__ {scalar_t__ xHandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEGGER_SYSVIEW_Warn (char*) ; 
 unsigned int SYSVIEW_FREERTOS_MAX_NOF_TASKS ; 
 TYPE_1__* _aTasks ; 

void SYSVIEW_DeleteTask(U32 xHandle) {
  unsigned n;

  for (n = 0; n < SYSVIEW_FREERTOS_MAX_NOF_TASKS; n++) {
    if (_aTasks[n].xHandle == xHandle) {
      break;
    }
  }
  if (n == SYSVIEW_FREERTOS_MAX_NOF_TASKS) {
    SEGGER_SYSVIEW_Warn("SYSTEMVIEW: Could not find task information. Cannot delete task.");
    return;
  }

  _aTasks[n].xHandle = 0;
}