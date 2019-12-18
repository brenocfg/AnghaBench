#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  timer_isr_handle_t ;
typedef  scalar_t__ timer_idx_t ;
typedef  int timer_group_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int ESP_INTR_FLAG_EDGE ; 
 scalar_t__ ETS_TG0_T0_EDGE_INTR_SOURCE ; 
 scalar_t__ ETS_TG0_T0_LEVEL_INTR_SOURCE ; 
 scalar_t__ ETS_TG1_T0_EDGE_INTR_SOURCE ; 
 scalar_t__ ETS_TG1_T0_LEVEL_INTR_SOURCE ; 
 int /*<<< orphan*/  TIMER_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TIMER_GROUP_0 129 
#define  TIMER_GROUP_1 128 
 int TIMER_GROUP_MAX ; 
 int /*<<< orphan*/  TIMER_GROUP_NUM_ERROR ; 
 scalar_t__ TIMER_MAX ; 
 int /*<<< orphan*/  TIMER_NUM_ERROR ; 
 int /*<<< orphan*/  TIMER_PARAM_ADDR_ERROR ; 
 int /*<<< orphan*/  TIMG_INT_ST_TIMERS_REG (int) ; 
 int /*<<< orphan*/  esp_intr_alloc_intrstatus (int,int,int /*<<< orphan*/ ,int,void (*) (void*),void*,int /*<<< orphan*/ *) ; 

esp_err_t timer_isr_register(timer_group_t group_num, timer_idx_t timer_num,
    void (*fn)(void*), void * arg, int intr_alloc_flags, timer_isr_handle_t *handle)
{
    TIMER_CHECK(group_num < TIMER_GROUP_MAX, TIMER_GROUP_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(timer_num < TIMER_MAX, TIMER_NUM_ERROR, ESP_ERR_INVALID_ARG);
    TIMER_CHECK(fn != NULL, TIMER_PARAM_ADDR_ERROR, ESP_ERR_INVALID_ARG);

    int intr_source = 0;
    uint32_t status_reg = 0;
    int mask = 0;
    switch(group_num) {
        case TIMER_GROUP_0:
        default:
            if((intr_alloc_flags & ESP_INTR_FLAG_EDGE) == 0) {
                intr_source = ETS_TG0_T0_LEVEL_INTR_SOURCE + timer_num;
            } else {
                intr_source = ETS_TG0_T0_EDGE_INTR_SOURCE + timer_num;
            }
            status_reg = TIMG_INT_ST_TIMERS_REG(0);
            mask = 1<<timer_num;
            break;
        case TIMER_GROUP_1:
            if((intr_alloc_flags & ESP_INTR_FLAG_EDGE) == 0) {
                intr_source = ETS_TG1_T0_LEVEL_INTR_SOURCE + timer_num;
            } else {
                intr_source = ETS_TG1_T0_EDGE_INTR_SOURCE + timer_num;
            }
            status_reg = TIMG_INT_ST_TIMERS_REG(1);
            mask = 1<<timer_num;
            break;
    }
    return esp_intr_alloc_intrstatus(intr_source, intr_alloc_flags, status_reg, mask, fn, arg, handle);
}