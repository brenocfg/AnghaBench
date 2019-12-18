#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  (* l1l2 ) (TYPE_4__*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {TYPE_4__ ifc; } ;
struct TYPE_12__ {scalar_t__ expires; } ;
struct TYPE_11__ {int l1_state; int l1_activated; TYPE_1__ d_if; TYPE_3__ t4_timer; TYPE_3__ t3_timer; } ;
typedef  TYPE_2__ hfcusb_data ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  HFCUSB_DBG_STATES ; 
 int HFC_TIMER_T4 ; 
 int HZ ; 
 int INDICATION ; 
 int /*<<< orphan*/  LED_S0_OFF ; 
 int /*<<< orphan*/  LED_S0_ON ; 
 int PH_ACTIVATE ; 
 int PH_DEACTIVATE ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  handle_led (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (TYPE_3__*) ; 

__attribute__((used)) static void
s0_state_handler(hfcusb_data * hfc, __u8 state)
{
	__u8 old_state;

	old_state = hfc->l1_state;
	if (state == old_state || state < 1 || state > 8)
		return;

	DBG(HFCUSB_DBG_STATES, "HFC-S USB: S0 statechange(%d -> %d)",
	    old_state, state);

	if (state < 4 || state == 7 || state == 8) {
		if (timer_pending(&hfc->t3_timer))
			del_timer(&hfc->t3_timer);
		DBG(HFCUSB_DBG_STATES, "HFC-S USB: T3 deactivated");
	}
	if (state >= 7) {
		if (timer_pending(&hfc->t4_timer))
			del_timer(&hfc->t4_timer);
		DBG(HFCUSB_DBG_STATES, "HFC-S USB: T4 deactivated");
	}

	if (state == 7 && !hfc->l1_activated) {
		hfc->d_if.ifc.l1l2(&hfc->d_if.ifc,
				   PH_ACTIVATE | INDICATION, NULL);
		DBG(HFCUSB_DBG_STATES, "HFC-S USB: PH_ACTIVATE | INDICATION sent");
		hfc->l1_activated = 1;
		handle_led(hfc, LED_S0_ON);
	} else if (state <= 3 /* && activated */ ) {
		if (old_state == 7 || old_state == 8) {
			DBG(HFCUSB_DBG_STATES, "HFC-S USB: T4 activated");
			if (!timer_pending(&hfc->t4_timer)) {
				hfc->t4_timer.expires =
				    jiffies + (HFC_TIMER_T4 * HZ) / 1000;
				add_timer(&hfc->t4_timer);
			}
		} else {
			hfc->d_if.ifc.l1l2(&hfc->d_if.ifc,
					   PH_DEACTIVATE | INDICATION,
					   NULL);
			DBG(HFCUSB_DBG_STATES,
			    "HFC-S USB: PH_DEACTIVATE | INDICATION sent");
			hfc->l1_activated = 0;
			handle_led(hfc, LED_S0_OFF);
		}
	}
	hfc->l1_state = state;
}