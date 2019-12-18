#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int arcofi_state; int /*<<< orphan*/  arcofi_wait; int /*<<< orphan*/  arcofitimer; TYPE_1__* arcofi_list; } ;
struct TYPE_6__ {TYPE_2__ isac; } ;
struct IsdnCardState {int debug; TYPE_3__ dc; int /*<<< orphan*/  HW_Flags; } ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  receive; } ;

/* Variables and functions */
#define  ARCOFI_NOP 130 
#define  ARCOFI_RECEIVE 129 
 int ARCOFI_RX_END ; 
 int ARCOFI_START ; 
 int ARCOFI_TIMEOUT ; 
#define  ARCOFI_TRANSMIT 128 
 int ARCOFI_TX_END ; 
 int /*<<< orphan*/  FLG_ARCOFI_ERROR ; 
 int /*<<< orphan*/  FLG_ARCOFI_TIMER ; 
 int L1_DEB_MONITOR ; 
 int /*<<< orphan*/  add_arcofi_timer (struct IsdnCardState*) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int,...) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_arcofi (struct IsdnCardState*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int
arcofi_fsm(struct IsdnCardState *cs, int event, void *data) {
	if (cs->debug & L1_DEB_MONITOR) {
		debugl1(cs, "arcofi state %d event %d", cs->dc.isac.arcofi_state, event);
	}
	if (event == ARCOFI_TIMEOUT) {
		cs->dc.isac.arcofi_state = ARCOFI_NOP;
		test_and_set_bit(FLG_ARCOFI_ERROR, &cs->HW_Flags);
		wake_up(&cs->dc.isac.arcofi_wait);
 		return(1);
	}
	switch (cs->dc.isac.arcofi_state) {
		case ARCOFI_NOP:
			if (event == ARCOFI_START) {
				cs->dc.isac.arcofi_list = data;
				cs->dc.isac.arcofi_state = ARCOFI_TRANSMIT;
				send_arcofi(cs);
			}
			break;
		case ARCOFI_TRANSMIT:
			if (event == ARCOFI_TX_END) {
				if (cs->dc.isac.arcofi_list->receive) {
					add_arcofi_timer(cs);
					cs->dc.isac.arcofi_state = ARCOFI_RECEIVE;
				} else {
					if (cs->dc.isac.arcofi_list->next) {
						cs->dc.isac.arcofi_list =
							cs->dc.isac.arcofi_list->next;
						send_arcofi(cs);
					} else {
						if (test_and_clear_bit(FLG_ARCOFI_TIMER, &cs->HW_Flags)) {
							del_timer(&cs->dc.isac.arcofitimer);
						}
						cs->dc.isac.arcofi_state = ARCOFI_NOP;
						wake_up(&cs->dc.isac.arcofi_wait);
					}
				}
			}
			break;
		case ARCOFI_RECEIVE:
			if (event == ARCOFI_RX_END) {
				if (cs->dc.isac.arcofi_list->next) {
					cs->dc.isac.arcofi_list =
						cs->dc.isac.arcofi_list->next;
					cs->dc.isac.arcofi_state = ARCOFI_TRANSMIT;
					send_arcofi(cs);
				} else {
					if (test_and_clear_bit(FLG_ARCOFI_TIMER, &cs->HW_Flags)) {
						del_timer(&cs->dc.isac.arcofitimer);
					}
					cs->dc.isac.arcofi_state = ARCOFI_NOP;
					wake_up(&cs->dc.isac.arcofi_wait);
				}
			}
			break;
		default:
			debugl1(cs, "Arcofi unknown state %x", cs->dc.isac.arcofi_state);
			return(2);
	}
	return(0);
}