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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ hci_inited; scalar_t__ hci_cmddone; int /*<<< orphan*/ * usrdata; int /*<<< orphan*/ * cb; int /*<<< orphan*/  timer_svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  SYS_RemoveAlarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bte_shutdown_finished ; 
 int /*<<< orphan*/  __bte_waitcmdfinish (TYPE_1__*) ; 
 TYPE_1__ btstate ; 
 int /*<<< orphan*/  hci_arg (TYPE_1__*) ; 
 int /*<<< orphan*/  hci_cmd_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_reset () ; 
 int /*<<< orphan*/  physbusif_shutdown () ; 

void BTE_Shutdown()
{
	u32 level;

	if(btstate.hci_inited==0) return;

	LOG("BTE_Shutdown()\n");

	_CPU_ISR_Disable(level);
	SYS_RemoveAlarm(btstate.timer_svc);
	btstate.cb = NULL;
	btstate.usrdata = NULL;
	btstate.hci_cmddone = 0;
	hci_arg(&btstate);
	hci_cmd_complete(__bte_shutdown_finished);
	hci_reset();
	__bte_waitcmdfinish(&btstate);
	_CPU_ISR_Restore(level);

	physbusif_shutdown();
}