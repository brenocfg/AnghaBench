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
typedef  scalar_t__ U8 ;
struct TYPE_4__ {scalar_t__ EventOffset; struct TYPE_4__ const* pNext; } ;
typedef  TYPE_1__ const SEGGER_SYSVIEW_MODULE ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_U32 (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (scalar_t__) ; 
 scalar_t__ SEGGER_SYSVIEW_INFO_SIZE ; 
 scalar_t__ SEGGER_SYSVIEW_MAX_STRING_LEN ; 
 int SEGGER_SYSVIEW_QUANTA_U32 ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_MODULEDESC ; 
 scalar_t__* _EncodeStr (scalar_t__*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  _SendPacket (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ const* _pFirstModule ; 

void SEGGER_SYSVIEW_RecordModuleDescription(const SEGGER_SYSVIEW_MODULE* pModule, const char* sDescription) {
  U8  ModuleId;
  SEGGER_SYSVIEW_MODULE* p;

  p = _pFirstModule;
  ModuleId = 0;
  do {
    if (p == pModule) {
      break;
    }
    ModuleId++;
    p = p->pNext;
  } while (p);
  {
    U8* pPayload;
    U8* pPayloadStart;
    RECORD_START(SEGGER_SYSVIEW_INFO_SIZE + 2 * SEGGER_SYSVIEW_QUANTA_U32 + 1 + SEGGER_SYSVIEW_MAX_STRING_LEN);
    //
    pPayload = pPayloadStart;
    //
    // Send module description
    // Send event offset and number of events
    //
    ENCODE_U32(pPayload, ModuleId);
    ENCODE_U32(pPayload, (pModule->EventOffset));
    pPayload = _EncodeStr(pPayload, sDescription, SEGGER_SYSVIEW_MAX_STRING_LEN);
    _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_MODULEDESC);
    RECORD_END();
  }
}