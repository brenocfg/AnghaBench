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
struct TYPE_4__ {int /*<<< orphan*/  (* pfSendModuleDesc ) () ;struct TYPE_4__* pNext; scalar_t__ NumEvents; scalar_t__ EventOffset; } ;
typedef  TYPE_1__ SEGGER_SYSVIEW_MODULE ;

/* Variables and functions */
 scalar_t__ MODULE_EVENT_OFFSET ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_LOCK () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_SendModule (int) ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_UNLOCK () ; 
 int _NumModules ; 
 TYPE_1__* _pFirstModule ; 
 int /*<<< orphan*/  stub1 () ; 

void SEGGER_SYSVIEW_RegisterModule(SEGGER_SYSVIEW_MODULE* pModule) {
  SEGGER_SYSVIEW_LOCK();
  if (_pFirstModule == 0) {
    //
    // No module registered, yet.
    // Start list with new module.
    // EventOffset is the base offset for modules
    //
    pModule->EventOffset = MODULE_EVENT_OFFSET;
    pModule->pNext = 0;
    _pFirstModule = pModule;
    _NumModules = 1;
  } else {
    //
    // Registreded module(s) present.
    // Prepend new module in list.
    // EventOffset set from number of events and offset of previous module.
    //
    pModule->EventOffset = _pFirstModule->EventOffset + _pFirstModule->NumEvents;
    pModule->pNext = _pFirstModule;
    _pFirstModule = pModule;
    _NumModules++;
  }
  SEGGER_SYSVIEW_SendModule(_NumModules-1);
  if (pModule->pfSendModuleDesc) {
    pModule->pfSendModuleDesc();
  }
  SEGGER_SYSVIEW_UNLOCK();
}