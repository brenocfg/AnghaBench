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
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int rstb_wait; int start_wait; int standby_wait; int sample_cycle; } ;
struct TYPE_4__ {int rstb_wait; int xpd_wait; int standby_wait; } ;
struct TYPE_6__ {TYPE_2__ saradc_fsm; TYPE_1__ saradc_fsm_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__ SYSCON ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

__attribute__((used)) static esp_err_t adc_set_fsm_time(int rst_wait, int start_wait, int standby_wait, int sample_cycle)
{
    portENTER_CRITICAL(&rtc_spinlock);
#if CONFIG_IDF_TARGET_ESP32
    // Internal FSM reset wait time
    if (rst_wait >= 0) {
        SYSCON.saradc_fsm.rstb_wait = rst_wait;
    }
    // Internal FSM start wait time
    if (start_wait >= 0) {
        SYSCON.saradc_fsm.start_wait = start_wait;
    }
    // Internal FSM standby wait time
    if (standby_wait >= 0) {
        SYSCON.saradc_fsm.standby_wait = standby_wait;
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    // Internal FSM reset wait time
    if (rst_wait >= 0) {
        SYSCON.saradc_fsm_wait.rstb_wait = rst_wait;
    }
    // Internal FSM start wait time
    if (start_wait >= 0) {
        SYSCON.saradc_fsm_wait.xpd_wait = start_wait;
    }
    // Internal FSM standby wait time
    if (standby_wait >= 0) {
        SYSCON.saradc_fsm_wait.standby_wait = standby_wait;
    }
#endif
    // Internal FSM standby sample cycle
    if (sample_cycle >= 0) {
        SYSCON.saradc_fsm.sample_cycle = sample_cycle;
    }
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}