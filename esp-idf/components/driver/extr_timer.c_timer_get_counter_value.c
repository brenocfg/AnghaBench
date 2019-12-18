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
typedef  int uint64_t ;
typedef  size_t timer_idx_t ;
typedef  size_t timer_group_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {TYPE_1__* hw_timer; } ;
struct TYPE_3__ {int update; int cnt_low; scalar_t__ cnt_high; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__** TG ; 
 int /*<<< orphan*/  TIMER_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TIMER_GROUP_MAX ; 
 int /*<<< orphan*/  TIMER_GROUP_NUM_ERROR ; 
 size_t TIMER_MAX ; 
 int /*<<< orphan*/  TIMER_NUM_ERROR ; 
 int /*<<< orphan*/  TIMER_PARAM_ADDR_ERROR ; 
 int /*<<< orphan*/  portENTER_CRITICAL_SAFE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL_SAFE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * timer_spinlock ; 

esp_err_t timer_get_counter_value(timer_group_t group_num, timer_idx_t timer_num, uint64_t* timer_val)
{
    TIMER_CHECK(group_num < TIMER_GROUP_MAX, TIMER_GROUP_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(timer_num < TIMER_MAX, TIMER_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(timer_val != NULL, TIMER_PARAM_ADDR_ERROR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL_SAFE(&timer_spinlock[group_num]);
#ifdef CONFIG_IDF_TARGET_ESP32
    TG[group_num]->hw_timer[timer_num].update = 1;
#elif defined CONFIG_IDF_TARGET_ESP32S2BETA
    TG[group_num]->hw_timer[timer_num].update.update = 1;
#endif
    *timer_val = ((uint64_t) TG[group_num]->hw_timer[timer_num].cnt_high << 32)
        | (TG[group_num]->hw_timer[timer_num].cnt_low);
    portEXIT_CRITICAL_SAFE(&timer_spinlock[group_num]);
    return ESP_OK;
}