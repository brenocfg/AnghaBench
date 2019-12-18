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
 int /*<<< orphan*/  RECORD_END () ; 
 int /*<<< orphan*/  RECORD_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_INFO_SIZE ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_ISR_EXIT ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SEGGER_SYSVIEW_RecordExitISR(void) {
  U8* pPayloadStart;
  RECORD_START(SEGGER_SYSVIEW_INFO_SIZE);
  //
  _SendPacket(pPayloadStart, pPayloadStart, SYSVIEW_EVTID_ISR_EXIT);
  RECORD_END();
}