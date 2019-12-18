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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  size_t timer_idx_t ;
typedef  size_t timer_group_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_2__* hw_timer; } ;
struct TYPE_4__ {int enable; scalar_t__ divider; } ;
struct TYPE_5__ {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIVIDER_RANGE_ERROR ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__** TG ; 
 int /*<<< orphan*/  TIMER_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 size_t TIMER_GROUP_MAX ; 
 int /*<<< orphan*/  TIMER_GROUP_NUM_ERROR ; 
 size_t TIMER_MAX ; 
 int /*<<< orphan*/  TIMER_NUM_ERROR ; 
 int /*<<< orphan*/ * timer_spinlock ; 

esp_err_t timer_set_divider(timer_group_t group_num, timer_idx_t timer_num, uint32_t divider)
{
    TIMER_CHECK(group_num < TIMER_GROUP_MAX, TIMER_GROUP_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(timer_num < TIMER_MAX, TIMER_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(divider > 1 && divider < 65537, DIVIDER_RANGE_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_ENTER_CRITICAL(&timer_spinlock[group_num]);
    int timer_en = TG[group_num]->hw_timer[timer_num].config.enable;
    TG[group_num]->hw_timer[timer_num].config.enable = 0;
    TG[group_num]->hw_timer[timer_num].config.divider = (uint16_t) divider;
    TG[group_num]->hw_timer[timer_num].config.enable = timer_en;
    TIMER_EXIT_CRITICAL(&timer_spinlock[group_num]);
    return ESP_OK;
}