#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * tmr; } ;
struct TYPE_7__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * tmr; } ;
struct TYPE_9__ {scalar_t__ active_level; scalar_t__ state; TYPE_3__ tap_rls_cb; TYPE_2__ tap_short_cb; TYPE_1__ press_serial_cb; TYPE_5__* cb_head; int /*<<< orphan*/  io_num; } ;
typedef  TYPE_4__ button_dev_t ;
struct TYPE_10__ {struct TYPE_10__* next_cb; int /*<<< orphan*/ * tmr; TYPE_4__* pbtn; } ;
typedef  TYPE_5__ button_cb_t ;

/* Variables and functions */
 scalar_t__ BUTTON_STATE_IDLE ; 
 scalar_t__ BUTTON_STATE_PUSH ; 
 int /*<<< orphan*/  STOP_TIMER (int /*<<< orphan*/ *) ; 
 scalar_t__ gpio_get_level (int /*<<< orphan*/ ) ; 
 scalar_t__ pvTimerGetTimerID (void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void button_tap_rls_cb(void* tmr)
{
    #if !USE_ESP_TIMER
    button_cb_t* btn_cb = (button_cb_t*) pvTimerGetTimerID(tmr);
    #else
    button_cb_t* btn_cb = (button_cb_t*)(tmr);
    #endif
    button_dev_t* btn = btn_cb->pbtn;
    STOP_TIMER(btn->tap_rls_cb.tmr);

    if (btn->active_level == gpio_get_level(btn->io_num)) {

    } else {
        // high, then key is up
        button_cb_t *pcb = btn->cb_head;
        while (pcb != NULL) {
            if (pcb->tmr != NULL) {
                STOP_TIMER(pcb->tmr);
            }
            pcb = pcb->next_cb;
        }
        if (btn->press_serial_cb.tmr && btn->press_serial_cb.tmr != NULL) {
            STOP_TIMER(btn->press_serial_cb.tmr);
        }
        if (btn->tap_short_cb.cb && btn->state == BUTTON_STATE_PUSH) {
            btn->tap_short_cb.cb(btn->tap_short_cb.arg);
        }
        if(btn->tap_rls_cb.cb && btn->state != BUTTON_STATE_IDLE) {
            btn->tap_rls_cb.cb(btn->tap_rls_cb.arg);
        }
        btn->state = BUTTON_STATE_IDLE;
    }
}