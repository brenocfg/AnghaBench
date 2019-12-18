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
typedef  scalar_t__ U8 ;
typedef  scalar_t__ U32 ;
struct TYPE_3__ {scalar_t__ EventOffset; int /*<<< orphan*/  sModule; struct TYPE_3__* pNext; } ;
typedef  TYPE_1__ SEGGER_SYSVIEW_MODULE ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_U32 (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (scalar_t__) ; 
 scalar_t__ SEGGER_SYSVIEW_INFO_SIZE ; 
 scalar_t__ SEGGER_SYSVIEW_MAX_STRING_LEN ; 
 int SEGGER_SYSVIEW_QUANTA_U32 ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_MODULEDESC ; 
 scalar_t__* _EncodeStr (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _SendPacket (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* _pFirstModule ; 

void SEGGER_SYSVIEW_SendModule(U8 ModuleId) {
  SEGGER_SYSVIEW_MODULE* pModule;
  U32 n;

  if (_pFirstModule != 0) {
    pModule = _pFirstModule;
    for (n = 0; n < ModuleId; n++) {
      pModule = pModule->pNext;
      if (pModule == 0) {
        break;
      }
    }
    if (pModule != 0) {
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
      pPayload = _EncodeStr(pPayload, pModule->sModule, SEGGER_SYSVIEW_MAX_STRING_LEN);
      _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_MODULEDESC);
      RECORD_END();
    }
  }
}