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
typedef  int /*<<< orphan*/  U8 ;
typedef  unsigned int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_U32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (scalar_t__) ; 
 scalar_t__ SEGGER_SYSVIEW_INFO_SIZE ; 
 int SEGGER_SYSVIEW_QUANTA_U32 ; 
 unsigned int SHRINK_ID (unsigned int) ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_TASK_STOP_READY ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SEGGER_SYSVIEW_OnTaskStopReady(U32 TaskId, unsigned int Cause) {
  U8* pPayload;
  U8* pPayloadStart;
  RECORD_START(SEGGER_SYSVIEW_INFO_SIZE + 2 * SEGGER_SYSVIEW_QUANTA_U32);
  //
  pPayload = pPayloadStart;
  TaskId = SHRINK_ID(TaskId);
  ENCODE_U32(pPayload, TaskId);
  ENCODE_U32(pPayload, Cause);
  _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_TASK_STOP_READY);
  RECORD_END();
}