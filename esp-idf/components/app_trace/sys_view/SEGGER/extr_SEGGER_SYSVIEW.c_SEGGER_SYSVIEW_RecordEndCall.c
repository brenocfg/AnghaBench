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

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_U32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (scalar_t__) ; 
 scalar_t__ SEGGER_SYSVIEW_INFO_SIZE ; 
 scalar_t__ SEGGER_SYSVIEW_QUANTA_U32 ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_END_CALL ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SEGGER_SYSVIEW_RecordEndCall(unsigned int EventID) {
  U8* pPayload;
  U8* pPayloadStart;
  RECORD_START(SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32);
  //
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, EventID);
  _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_END_CALL);
  RECORD_END();
}