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
typedef  void* U32 ;
typedef  int /*<<< orphan*/  TaskInfo ;
struct TYPE_4__ {char const* sName; unsigned int Prio; unsigned int StackSize; void* StackBase; void* TaskID; } ;
typedef  TYPE_1__ SEGGER_SYSVIEW_TASKINFO ;

/* Variables and functions */
 int /*<<< orphan*/  SEGGER_SYSVIEW_SendTaskInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void SYSVIEW_SendTaskInfo(U32 TaskID, const char* sName, unsigned Prio, U32 StackBase, unsigned StackSize) {
  SEGGER_SYSVIEW_TASKINFO TaskInfo;

  memset(&TaskInfo, 0, sizeof(TaskInfo)); // Fill all elements with 0 to allow extending the structure in future version without breaking the code
  TaskInfo.TaskID     = TaskID;
  TaskInfo.sName      = sName;
  TaskInfo.Prio       = Prio;
  TaskInfo.StackBase  = StackBase;
  TaskInfo.StackSize  = StackSize;
  SEGGER_SYSVIEW_SendTaskInfo(&TaskInfo);
}