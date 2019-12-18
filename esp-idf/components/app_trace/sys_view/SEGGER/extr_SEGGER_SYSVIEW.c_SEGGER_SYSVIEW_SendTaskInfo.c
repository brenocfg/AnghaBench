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
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_3__ {int /*<<< orphan*/  StackSize; int /*<<< orphan*/  StackBase; int /*<<< orphan*/  TaskID; int /*<<< orphan*/  sName; int /*<<< orphan*/  Prio; } ;
typedef  TYPE_1__ SEGGER_SYSVIEW_TASKINFO ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (scalar_t__) ; 
 scalar_t__ SEGGER_SYSVIEW_INFO_SIZE ; 
 scalar_t__ SEGGER_SYSVIEW_QUANTA_U32 ; 
 int /*<<< orphan*/  SHRINK_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_STACK_INFO ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_TASK_INFO ; 
 int /*<<< orphan*/ * _EncodeStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SEGGER_SYSVIEW_SendTaskInfo(const SEGGER_SYSVIEW_TASKINFO *pInfo) {
  U8* pPayload;
  U8* pPayloadStart;
  RECORD_START(SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32 + 1 + 32);
  //
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, SHRINK_ID(pInfo->TaskID));
  ENCODE_U32(pPayload, pInfo->Prio);
  pPayload = _EncodeStr(pPayload, pInfo->sName, 32);
  _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_TASK_INFO);
  //
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, SHRINK_ID(pInfo->TaskID));
  ENCODE_U32(pPayload, pInfo->StackBase);
  ENCODE_U32(pPayload, pInfo->StackSize);
  ENCODE_U32(pPayload, 0); // Stack End, future use
  _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_STACK_INFO);
  RECORD_END();
}