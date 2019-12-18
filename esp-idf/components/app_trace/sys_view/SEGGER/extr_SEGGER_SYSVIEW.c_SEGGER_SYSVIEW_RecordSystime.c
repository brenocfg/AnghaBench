#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int U64 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_4__ {TYPE_1__* pOSAPI; } ;
struct TYPE_3__ {int (* pfGetTime ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SEGGER_SYSVIEW_GET_TIMESTAMP () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_RecordU32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_RecordU32x2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_SYSTIME_CYCLES ; 
 int /*<<< orphan*/  SYSVIEW_EVTID_SYSTIME_US ; 
 TYPE_2__ _SYSVIEW_Globals ; 
 int stub1 () ; 

void SEGGER_SYSVIEW_RecordSystime(void) {
  U64 Systime;

  if (_SYSVIEW_Globals.pOSAPI && _SYSVIEW_Globals.pOSAPI->pfGetTime) {
    Systime = _SYSVIEW_Globals.pOSAPI->pfGetTime();
    SEGGER_SYSVIEW_RecordU32x2(SYSVIEW_EVTID_SYSTIME_US,
                               (U32)(Systime),
                               (U32)(Systime >> 32));
  } else {
    SEGGER_SYSVIEW_RecordU32(SYSVIEW_EVTID_SYSTIME_CYCLES, SEGGER_SYSVIEW_GET_TIMESTAMP());
  }
}