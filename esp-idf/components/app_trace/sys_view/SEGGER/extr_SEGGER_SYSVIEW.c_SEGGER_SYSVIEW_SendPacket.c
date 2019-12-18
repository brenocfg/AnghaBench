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
 int /*<<< orphan*/  SEGGER_SYSVIEW_LOCK () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_UNLOCK () ; 
 int /*<<< orphan*/  _SendPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

int SEGGER_SYSVIEW_SendPacket(U8* pPacket, U8* pPayloadEnd, unsigned int EventId) {
#if (SEGGER_SYSVIEW_USE_STATIC_BUFFER == 1)
  SEGGER_SYSVIEW_LOCK();
#endif
  _SendPacket(pPacket + 4, pPayloadEnd, EventId);
#if (SEGGER_SYSVIEW_USE_STATIC_BUFFER == 1)
  SEGGER_SYSVIEW_UNLOCK();
#endif
  return 0;
}