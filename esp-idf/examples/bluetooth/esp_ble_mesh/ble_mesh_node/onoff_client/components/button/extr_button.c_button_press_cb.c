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
struct TYPE_3__ {scalar_t__ active_level; int /*<<< orphan*/  state; int /*<<< orphan*/  io_num; } ;
typedef  TYPE_1__ button_dev_t ;
struct TYPE_4__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ) ;TYPE_1__* pbtn; } ;
typedef  TYPE_2__ button_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON_STATE_PRESSED ; 
 scalar_t__ gpio_get_level (int /*<<< orphan*/ ) ; 
 scalar_t__ pvTimerGetTimerID (void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void button_press_cb(void* tmr)
{
    #if !USE_ESP_TIMER
    button_cb_t* btn_cb = (button_cb_t*) pvTimerGetTimerID(tmr);
    #else
    button_cb_t* btn_cb = (button_cb_t*)(tmr);
    #endif

    button_dev_t* btn = btn_cb->pbtn;
    // low, then restart
    if (btn->active_level == gpio_get_level(btn->io_num)) {
        btn->state = BUTTON_STATE_PRESSED;
        if (btn_cb->cb) {
            btn_cb->cb(btn_cb->arg);
        }
    }
}