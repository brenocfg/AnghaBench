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
typedef  void* U32 ;
struct TYPE_2__ {void* LastTxTimeStamp; void* DropCount; int /*<<< orphan*/  EnableState; } ;
typedef  void* I32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_ID_UP ; 
 int /*<<< orphan*/  ENCODE_U32 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  MAKE_DELTA_32BIT (void*) ; 
 int SEGGER_RTT_WriteSkipNoLock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* SEGGER_SYSVIEW_GET_TIMESTAMP () ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_OVERFLOW ; 
 TYPE_1__ _SYSVIEW_Globals ; 

__attribute__((used)) static int _TrySendOverflowPacket(void) {
  U32 TimeStamp;
  I32 Delta;
  int Status;
  U8  aPacket[11];
  U8* pPayload;

  aPacket[0] = SYSVIEW_EVTID_OVERFLOW;      // 1
  pPayload   = &aPacket[1];
  ENCODE_U32(pPayload, _SYSVIEW_Globals.DropCount);
  //
  // Compute time stamp delta and append it to packet.
  //
  TimeStamp  = SEGGER_SYSVIEW_GET_TIMESTAMP();
  Delta = TimeStamp - _SYSVIEW_Globals.LastTxTimeStamp;
  MAKE_DELTA_32BIT(Delta);
  ENCODE_U32(pPayload, Delta);
  //
  // Try to store packet in RTT buffer and update time stamp when this was successful
  //
  Status = SEGGER_RTT_WriteSkipNoLock(CHANNEL_ID_UP, aPacket, pPayload - aPacket);
  if (Status) {
    _SYSVIEW_Globals.LastTxTimeStamp = TimeStamp;
    _SYSVIEW_Globals.EnableState--; // EnableState has been 2, will be 1. Always.
  } else {
    _SYSVIEW_Globals.DropCount++;
  }
  //
  return Status;
}