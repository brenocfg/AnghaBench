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
 int SEGGER_SYSVIEW_MAX_ARGUMENTS ; 
 scalar_t__ SEGGER_SYSVIEW_MAX_STRING_LEN ; 
 int SEGGER_SYSVIEW_QUANTA_U32 ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_PRINT_FORMATTED ; 
 int /*<<< orphan*/ * _EncodeStr (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _APrintHost(const char* s, U32 Options, U32* pArguments, U32 NumArguments) {
  U8* pPayload;
  U8* pPayloadStart;

  RECORD_START(SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_MAX_STRING_LEN + 2 * SEGGER_SYSVIEW_QUANTA_U32 + SEGGER_SYSVIEW_MAX_ARGUMENTS * SEGGER_SYSVIEW_QUANTA_U32);
  pPayload = _EncodeStr(pPayloadStart, s, SEGGER_SYSVIEW_MAX_STRING_LEN);
  ENCODE_U32(pPayload, Options);
  ENCODE_U32(pPayload, NumArguments);
  while (NumArguments--) {
    ENCODE_U32(pPayload, (*pArguments++));
  }
  _SendPacket(pPayloadStart, pPayload, SYSVIEW_EVTID_PRINT_FORMATTED);
  RECORD_END();
}