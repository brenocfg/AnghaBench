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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  strState; int /*<<< orphan*/  strEvent; int /*<<< orphan*/  event_count; int /*<<< orphan*/  state_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L1SFnList ; 
 int /*<<< orphan*/  L1S_STATE_COUNT ; 
 int /*<<< orphan*/  L1_EVENT_COUNT ; 
 int /*<<< orphan*/ * debug ; 
 TYPE_1__ l1fsm_s ; 
 int /*<<< orphan*/  mISDN_FsmNew (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strL1Event ; 
 int /*<<< orphan*/  strL1SState ; 

int
l1_init(u_int *deb)
{
	debug = deb;
	l1fsm_s.state_count = L1S_STATE_COUNT;
	l1fsm_s.event_count = L1_EVENT_COUNT;
	l1fsm_s.strEvent = strL1Event;
	l1fsm_s.strState = strL1SState;
	mISDN_FsmNew(&l1fsm_s, L1SFnList, ARRAY_SIZE(L1SFnList));
	return 0;
}