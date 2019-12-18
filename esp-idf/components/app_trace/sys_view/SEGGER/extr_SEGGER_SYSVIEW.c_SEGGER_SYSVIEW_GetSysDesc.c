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
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* pfSendSysDesc ) () ;int /*<<< orphan*/  RAMBaseAddress; int /*<<< orphan*/  CPUFreq; int /*<<< orphan*/  SysFreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (scalar_t__) ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_ID_SHIFT ; 
 scalar_t__ SEGGER_SYSVIEW_INFO_SIZE ; 
 int SEGGER_SYSVIEW_QUANTA_U32 ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_INIT ; 
 TYPE_1__ _SYSVIEW_Globals ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

void SEGGER_SYSVIEW_GetSysDesc(void) {
  U8* pPayload;
  U8* pPayloadStart;
  RECORD_START(SEGGER_SYSVIEW_INFO_SIZE + 4 * SEGGER_SYSVIEW_QUANTA_U32);
  //
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, _SYSVIEW_Globals.SysFreq);
  ENCODE_U32(pPayload, _SYSVIEW_Globals.CPUFreq);
  ENCODE_U32(pPayload, _SYSVIEW_Globals.RAMBaseAddress);
  ENCODE_U32(pPayload, SEGGER_SYSVIEW_ID_SHIFT);
  _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_INIT);
  RECORD_END();
  if (_SYSVIEW_Globals.pfSendSysDesc) {
    _SYSVIEW_Globals.pfSendSysDesc();
  }
}