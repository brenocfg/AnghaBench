#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t timer_idx_t ;
typedef  size_t timer_group_t ;
struct TYPE_8__ {int divider; int /*<<< orphan*/  intr_type; int /*<<< orphan*/  counter_en; int /*<<< orphan*/  counter_dir; int /*<<< orphan*/  auto_reload; int /*<<< orphan*/  alarm_en; } ;
typedef  TYPE_3__ timer_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_9__ {TYPE_2__* hw_timer; } ;
struct TYPE_6__ {int divider; scalar_t__ level_int_en; int /*<<< orphan*/  enable; int /*<<< orphan*/  increase; int /*<<< orphan*/  autoreload; int /*<<< orphan*/  alarm_en; } ;
struct TYPE_7__ {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_5__** TG ; 
 int /*<<< orphan*/  TIMER_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 size_t TIMER_GROUP_MAX ; 
 int /*<<< orphan*/  TIMER_GROUP_NUM_ERROR ; 
 int /*<<< orphan*/  TIMER_INTR_LEVEL ; 
 size_t TIMER_MAX ; 
 int /*<<< orphan*/  TIMER_NUM_ERROR ; 
 int /*<<< orphan*/  TIMER_PARAM_ADDR_ERROR ; 
 int /*<<< orphan*/ * timer_spinlock ; 

esp_err_t timer_get_config(timer_group_t group_num, timer_idx_t timer_num, timer_config_t *config)
{
    TIMER_CHECK(group_num < TIMER_GROUP_MAX, TIMER_GROUP_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(timer_num < TIMER_MAX, TIMER_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(config != NULL, TIMER_PARAM_ADDR_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_ENTER_CRITICAL(&timer_spinlock[group_num]);
    config->alarm_en = TG[group_num]->hw_timer[timer_num].config.alarm_en;
    config->auto_reload = TG[group_num]->hw_timer[timer_num].config.autoreload;
    config->counter_dir = TG[group_num]->hw_timer[timer_num].config.increase;
    config->divider =  (TG[group_num]->hw_timer[timer_num].config.divider == 0 ?
        65536 : TG[group_num]->hw_timer[timer_num].config.divider);
    config->counter_en = TG[group_num]->hw_timer[timer_num].config.enable;
    if(TG[group_num]->hw_timer[timer_num].config.level_int_en) {
        config->intr_type = TIMER_INTR_LEVEL;
    }
    TIMER_EXIT_CRITICAL(&timer_spinlock[group_num]);
    return ESP_OK;
}