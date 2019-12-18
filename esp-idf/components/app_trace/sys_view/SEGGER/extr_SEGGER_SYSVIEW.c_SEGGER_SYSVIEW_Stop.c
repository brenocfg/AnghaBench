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
struct TYPE_2__ {scalar_t__ EnableState; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_INFO_SIZE ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_TRACE_STOP ; 
 TYPE_1__ _SYSVIEW_Globals ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SEGGER_SYSVIEW_Stop(void) {
  U8* pPayloadStart;
  RECORD_START(SEGGER_SYSVIEW_INFO_SIZE);
  //
  if (_SYSVIEW_Globals.EnableState) {
    _SendPacket(pPayloadStart, pPayloadStart, SYSVIEW_EVTID_TRACE_STOP);
    _SYSVIEW_Globals.EnableState = 0;
  }
  RECORD_END();
}