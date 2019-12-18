#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int U8 ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_ID_DOWN ; 
 int SEGGER_RTT_ReadNoLock (int /*<<< orphan*/ ,int*,int) ; 
#define  SEGGER_SYSVIEW_COMMAND_ID_GET_MODULE 135 
#define  SEGGER_SYSVIEW_COMMAND_ID_GET_MODULEDESC 134 
#define  SEGGER_SYSVIEW_COMMAND_ID_GET_NUMMODULES 133 
#define  SEGGER_SYSVIEW_COMMAND_ID_GET_SYSDESC 132 
#define  SEGGER_SYSVIEW_COMMAND_ID_GET_SYSTIME 131 
#define  SEGGER_SYSVIEW_COMMAND_ID_GET_TASKLIST 130 
#define  SEGGER_SYSVIEW_COMMAND_ID_START 129 
#define  SEGGER_SYSVIEW_COMMAND_ID_STOP 128 
 int /*<<< orphan*/  SEGGER_SYSVIEW_GetSysDesc () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_RecordSystime () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_SendModule (int) ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_SendModuleDescription () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_SendNumModules () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_SendTaskList () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_Start () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_Stop () ; 

__attribute__((used)) static void _HandleIncomingPacket(void) {
  U8  Cmd;
  int Status;
  //
  Status = SEGGER_RTT_ReadNoLock(CHANNEL_ID_DOWN, &Cmd, 1);
  if (Status > 0) {
    switch (Cmd) {
    case SEGGER_SYSVIEW_COMMAND_ID_START:
      SEGGER_SYSVIEW_Start();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_STOP:
      SEGGER_SYSVIEW_Stop();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_SYSTIME:
      SEGGER_SYSVIEW_RecordSystime();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_TASKLIST:
      SEGGER_SYSVIEW_SendTaskList();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_SYSDESC:
      SEGGER_SYSVIEW_GetSysDesc();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_NUMMODULES:
      SEGGER_SYSVIEW_SendNumModules();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_MODULEDESC:
      SEGGER_SYSVIEW_SendModuleDescription();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_MODULE:
      Status = SEGGER_RTT_ReadNoLock(CHANNEL_ID_DOWN, &Cmd, 1);
      if (Status > 0) {
        SEGGER_SYSVIEW_SendModule(Cmd);
      }
      break;
    default:
      if (Cmd >= 128) { // Unknown extended command. Dummy read its parameter.
        SEGGER_RTT_ReadNoLock(CHANNEL_ID_DOWN, &Cmd, 1);
      }
      break;
    }
  }
}