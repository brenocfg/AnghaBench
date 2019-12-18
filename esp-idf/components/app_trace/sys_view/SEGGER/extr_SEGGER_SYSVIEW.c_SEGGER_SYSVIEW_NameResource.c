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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (scalar_t__) ; 
 scalar_t__ SEGGER_SYSVIEW_INFO_SIZE ; 
 scalar_t__ SEGGER_SYSVIEW_MAX_STRING_LEN ; 
 scalar_t__ SEGGER_SYSVIEW_QUANTA_U32 ; 
 int /*<<< orphan*/  SHRINK_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_NAME_RESOURCE ; 
 int /*<<< orphan*/ * _EncodeStr (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SEGGER_SYSVIEW_NameResource(U32 ResourceId, const char* sName) {
  U8* pPayload;
  U8* pPayloadStart;
  RECORD_START(SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32 + 1 + SEGGER_SYSVIEW_MAX_STRING_LEN);
  //
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, SHRINK_ID(ResourceId));
  pPayload = _EncodeStr(pPayload, sName, SEGGER_SYSVIEW_MAX_STRING_LEN);
  _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_NAME_RESOURCE);
  RECORD_END();
}