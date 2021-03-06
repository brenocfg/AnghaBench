#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* l1l2 ) (TYPE_3__*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_3__ ifc; } ;
struct TYPE_8__ {scalar_t__ l1_activated; TYPE_1__ d_if; } ;
typedef  TYPE_2__ hfcusb_data ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HFCUSB_DBG_STATES ; 
 int /*<<< orphan*/  HFCUSB_STATES ; 
 int INDICATION ; 
 int /*<<< orphan*/  LED_S0_OFF ; 
 int PH_DEACTIVATE ; 
 int /*<<< orphan*/  handle_led (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_control_request (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_timer_expire_t3(hfcusb_data * hfc)
{
	hfc->d_if.ifc.l1l2(&hfc->d_if.ifc, PH_DEACTIVATE | INDICATION,
			   NULL);

	DBG(HFCUSB_DBG_STATES,
	    "HFC-S USB: PH_DEACTIVATE | INDICATION sent (T3 expire)");

	hfc->l1_activated = 0;
	handle_led(hfc, LED_S0_OFF);
	/* deactivate : */
	queue_control_request(hfc, HFCUSB_STATES, 0x10, 1);
	queue_control_request(hfc, HFCUSB_STATES, 3, 1);
}