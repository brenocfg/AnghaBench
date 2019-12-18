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
typedef  scalar_t__ uint64_t ;
typedef  double uint16_t ;
typedef  size_t timer_idx_t ;
typedef  size_t timer_group_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_6__ {TYPE_2__* hw_timer; } ;
struct TYPE_4__ {double divider; scalar_t__ use_xtal; } ;
struct TYPE_5__ {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_OK ; 
 TYPE_3__** TG ; 
 double TIMER_BASE_CLK ; 
 int /*<<< orphan*/  TIMER_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TIMER_GROUP_MAX ; 
 int /*<<< orphan*/  TIMER_GROUP_NUM_ERROR ; 
 size_t TIMER_MAX ; 
 int /*<<< orphan*/  TIMER_NUM_ERROR ; 
 int /*<<< orphan*/  TIMER_PARAM_ADDR_ERROR ; 
 double rtc_clk_apb_freq_get () ; 
 scalar_t__ rtc_clk_xtal_freq_get () ; 
 scalar_t__ timer_get_counter_value (size_t,size_t,scalar_t__*) ; 

esp_err_t timer_get_counter_time_sec(timer_group_t group_num, timer_idx_t timer_num, double* time)
{
    TIMER_CHECK(group_num < TIMER_GROUP_MAX, TIMER_GROUP_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(timer_num < TIMER_MAX, TIMER_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(time != NULL, TIMER_PARAM_ADDR_ERROR, ESP_ERR_INVALID_ARG);

    uint64_t timer_val;
    esp_err_t err = timer_get_counter_value(group_num, timer_num, &timer_val);
    if (err == ESP_OK) {
        uint16_t div = TG[group_num]->hw_timer[timer_num].config.divider;
#ifdef CONFIG_IDF_TARGET_ESP32
        *time = (double)timer_val * div / TIMER_BASE_CLK;
#elif defined CONFIG_IDF_TARGET_ESP32S2BETA
        if(TG[group_num]->hw_timer[timer_num].config.use_xtal) {
            *time = (double)timer_val * div / ((int)rtc_clk_xtal_freq_get() * 1000000);
        } else {
            *time = (double)timer_val * div / rtc_clk_apb_freq_get();
        }
#endif
    }
    return err;
}