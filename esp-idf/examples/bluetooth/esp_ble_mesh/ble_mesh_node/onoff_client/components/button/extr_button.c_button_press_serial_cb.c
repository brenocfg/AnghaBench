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
struct TYPE_3__ {int interval; int /*<<< orphan*/  tmr; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ press_serial_cb; } ;
typedef  TYPE_2__ button_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_timer_start_once (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_timer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ pvTimerGetTimerID (void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTimerChangePeriod (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTimerReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void button_press_serial_cb(void* tmr)
{
    #if !USE_ESP_TIMER
    button_dev_t* btn = (button_dev_t*) pvTimerGetTimerID(tmr);
    #else
    button_dev_t* btn = (button_dev_t*)(tmr);
    #endif

    if (btn->press_serial_cb.cb) {
        btn->press_serial_cb.cb(btn->press_serial_cb.arg);
    }
    #if !USE_ESP_TIMER
    xTimerChangePeriod(btn->press_serial_cb.tmr, btn->press_serial_cb.interval, portMAX_DELAY);
    xTimerReset(btn->press_serial_cb.tmr, portMAX_DELAY);
    #else
    esp_timer_stop(btn->press_serial_cb.tmr);
    esp_timer_start_once(btn->press_serial_cb.tmr, btn->press_serial_cb.interval * portTICK_PERIOD_MS * 1000);
    #endif
}