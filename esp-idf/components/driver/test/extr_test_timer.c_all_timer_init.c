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
typedef  int /*<<< orphan*/  timer_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TIMER_0 ; 
 int /*<<< orphan*/  TIMER_1 ; 
 int /*<<< orphan*/  TIMER_GROUP_0 ; 
 int /*<<< orphan*/  TIMER_GROUP_1 ; 
 scalar_t__ timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void all_timer_init(timer_config_t config, bool flag)
{
    esp_err_t ret;
    ret = timer_init(TIMER_GROUP_0, TIMER_0, &config);
    if (flag) {
        TEST_ASSERT(ret == ESP_OK);
    } else {
        TEST_ASSERT(ret == ESP_ERR_INVALID_ARG);
    }
    ret = timer_init(TIMER_GROUP_0, TIMER_1, &config);
    if (flag) {
        TEST_ASSERT(ret == ESP_OK);
    } else {
        TEST_ASSERT(ret == ESP_ERR_INVALID_ARG);
    }
    ret = timer_init(TIMER_GROUP_1, TIMER_0, &config);
    if (flag) {
        TEST_ASSERT(ret == ESP_OK);
    } else {
        TEST_ASSERT(ret == ESP_ERR_INVALID_ARG);
    }
    ret = timer_init(TIMER_GROUP_1, TIMER_1, &config);
    if (flag) {
        TEST_ASSERT(ret == ESP_OK);
    } else {
        TEST_ASSERT(ret == ESP_ERR_INVALID_ARG);
    }
}