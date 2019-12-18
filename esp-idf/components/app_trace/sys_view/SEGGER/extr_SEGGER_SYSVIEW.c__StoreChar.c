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
typedef  unsigned int U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_3__ {unsigned int Cnt; unsigned int* pPayload; unsigned int* pPayloadStart; int /*<<< orphan*/  pBuffer; int /*<<< orphan*/  Options; } ;
typedef  TYPE_1__ SEGGER_SYSVIEW_PRINTF_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_U32 (unsigned int*,int /*<<< orphan*/ ) ; 
 unsigned int SEGGER_SYSVIEW_MAX_STRING_LEN ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_PRINT_FORMATTED ; 
 unsigned int* _PreparePacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SendPacket (unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _StoreChar(SEGGER_SYSVIEW_PRINTF_DESC * p, char c) {
  unsigned int  Cnt;
  U8*           pPayload;
  U32           Options;

  Cnt = p->Cnt;
  if ((Cnt + 1u) <= SEGGER_SYSVIEW_MAX_STRING_LEN) {
    *(p->pPayload++) = c;
    p->Cnt = Cnt + 1u;
  }
  //
  // Write part of string, when the buffer is full
  //
  if (p->Cnt == SEGGER_SYSVIEW_MAX_STRING_LEN) {
    *(p->pPayloadStart) = p->Cnt;
    pPayload = p->pPayload;
    Options = p->Options;
    ENCODE_U32(pPayload, Options);
    ENCODE_U32(pPayload, 0);
    _SendPacket(p->pPayloadStart, pPayload, SYSVIEW_EVTID_PRINT_FORMATTED);
    p->pPayloadStart = _PreparePacket(p->pBuffer);
    p->pPayload = p->pPayloadStart + 1u;
    p->Cnt = 0u;
  }
}