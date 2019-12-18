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
typedef  int /*<<< orphan*/  u32 ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct bt_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer_svc; int /*<<< orphan*/  hci_cmdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CreateAlarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_SetPeriodicAlarm (int /*<<< orphan*/ ,struct timespec*,struct timespec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_conn_complete ; 
 int /*<<< orphan*/  acl_wlp_completed ; 
 int /*<<< orphan*/  bt_alarmhandler ; 
 int /*<<< orphan*/  bte_reset_all () ; 
 TYPE_1__ btstate ; 
 int /*<<< orphan*/  hci_connection_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_init () ; 
 int /*<<< orphan*/  hci_reset_all () ; 
 int /*<<< orphan*/  hci_wlp_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_init () ; 
 int /*<<< orphan*/  l2cap_reset_all () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  physbusif_init () ; 
 int /*<<< orphan*/  physbusif_reset_all () ; 

void BTE_Init()
{
	u32 level;
	struct timespec tb;

	LOG("BTE_Init()\n");

	memset(&btstate,0,sizeof(struct bt_state));

	hci_init();
	l2cap_init();
	physbusif_init();

	LWP_InitQueue(&btstate.hci_cmdq);
	SYS_CreateAlarm(&btstate.timer_svc);

	_CPU_ISR_Disable(level);
	bte_reset_all();
	hci_reset_all();
	l2cap_reset_all();
	physbusif_reset_all();

	hci_wlp_complete(acl_wlp_completed);
	hci_connection_complete(acl_conn_complete);
	_CPU_ISR_Restore(level);

	tb.tv_sec = 1;
	tb.tv_nsec = 0;
	SYS_SetPeriodicAlarm(btstate.timer_svc,&tb,&tb,bt_alarmhandler, NULL);
}