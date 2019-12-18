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
struct HvLpEvent {int xSubtype; int /*<<< orphan*/  xRc; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvCallEvent_ackLpEvent (struct HvLpEvent*) ; 
 int /*<<< orphan*/  HvLpEvent_Rc_InvalidSubtype ; 
 int VIOMINOR_SUBTYPE_MASK ; 
 int /*<<< orphan*/  hvc_ack_event (struct HvLpEvent*) ; 
 int /*<<< orphan*/  hvc_close_event (struct HvLpEvent*) ; 
 int /*<<< orphan*/  hvc_config_event (struct HvLpEvent*) ; 
 int /*<<< orphan*/  hvc_data_event (struct HvLpEvent*) ; 
 int /*<<< orphan*/  hvc_open_event (struct HvLpEvent*) ; 
 int /*<<< orphan*/  hvlpevent_is_int (struct HvLpEvent*) ; 
 int /*<<< orphan*/  hvlpevent_need_ack (struct HvLpEvent*) ; 
#define  viocharack 132 
#define  viocharclose 131 
#define  viocharconfig 130 
#define  viochardata 129 
#define  viocharopen 128 

__attribute__((used)) static void hvc_handle_event(struct HvLpEvent *event)
{
	int charminor;

	if (event == NULL)
		return;

	charminor = event->xSubtype & VIOMINOR_SUBTYPE_MASK;
	switch (charminor) {
	case viocharopen:
		hvc_open_event(event);
		break;
	case viocharclose:
		hvc_close_event(event);
		break;
	case viochardata:
		hvc_data_event(event);
		break;
	case viocharack:
		hvc_ack_event(event);
		break;
	case viocharconfig:
		hvc_config_event(event);
		break;
	default:
		if (hvlpevent_is_int(event) && hvlpevent_need_ack(event)) {
			event->xRc = HvLpEvent_Rc_InvalidSubtype;
			HvCallEvent_ackLpEvent(event);
		}
	}
}