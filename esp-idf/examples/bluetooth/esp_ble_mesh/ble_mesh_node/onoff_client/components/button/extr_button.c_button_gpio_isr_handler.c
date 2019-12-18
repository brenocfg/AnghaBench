#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ portBASE_TYPE ;
struct TYPE_6__ {int interval; int /*<<< orphan*/ * tmr; } ;
struct TYPE_5__ {int interval; int /*<<< orphan*/ * tmr; } ;
struct TYPE_7__ {int active_level; TYPE_2__ tap_rls_cb; TYPE_4__* cb_head; TYPE_1__ tap_psh_cb; int /*<<< orphan*/  io_num; } ;
typedef  TYPE_3__ button_dev_t ;
struct TYPE_8__ {int interval; struct TYPE_8__* next_cb; int /*<<< orphan*/ * tmr; } ;
typedef  TYPE_4__ button_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_timer_start_once (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  esp_timer_stop (int /*<<< orphan*/ *) ; 
 int gpio_get_level (int /*<<< orphan*/ ) ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdTRUE ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  portYIELD_FROM_ISR () ; 
 int /*<<< orphan*/  xTimerResetFromISR (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  xTimerStopFromISR (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void button_gpio_isr_handler(void* arg)
{
    button_dev_t* btn = (button_dev_t*) arg;
    portBASE_TYPE HPTaskAwoken = pdFALSE;
    int level = gpio_get_level(btn->io_num);
    if (level == btn->active_level) {
        if (btn->tap_psh_cb.tmr) {
            #if !USE_ESP_TIMER
            xTimerStopFromISR(btn->tap_psh_cb.tmr, &HPTaskAwoken);
            xTimerResetFromISR(btn->tap_psh_cb.tmr, &HPTaskAwoken);
            #else 
            esp_timer_stop(btn->tap_psh_cb.tmr);
            esp_timer_start_once(btn->tap_psh_cb.tmr, btn->tap_psh_cb.interval * portTICK_PERIOD_MS * 1000);
            #endif
        }

        button_cb_t *pcb = btn->cb_head;
        while (pcb != NULL) {
            if (pcb->tmr != NULL) {
                #if !USE_ESP_TIMER
                xTimerStopFromISR(pcb->tmr, &HPTaskAwoken);
                xTimerResetFromISR(pcb->tmr, &HPTaskAwoken);
                #else
                esp_timer_stop(pcb->tmr);
                esp_timer_start_once(pcb->tmr, pcb->interval * portTICK_PERIOD_MS * 1000);
                #endif
            }
            pcb = pcb->next_cb;
        }
    } else {
        // 50ms, check if this is a real key up
        if (btn->tap_rls_cb.tmr) {
            #if !USE_ESP_TIMER
            xTimerStopFromISR(btn->tap_rls_cb.tmr, &HPTaskAwoken);
            xTimerResetFromISR(btn->tap_rls_cb.tmr, &HPTaskAwoken);
            #else
            esp_timer_stop(btn->tap_rls_cb.tmr);
            esp_timer_start_once(btn->tap_rls_cb.tmr, btn->tap_rls_cb.interval * portTICK_PERIOD_MS * 1000);
            #endif
        }
    }
    if(HPTaskAwoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}