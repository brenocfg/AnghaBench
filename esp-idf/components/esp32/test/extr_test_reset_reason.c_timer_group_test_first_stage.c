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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ RESET_REASON ;

/* Variables and functions */
 scalar_t__ POWERON_RESET ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TIMER_0 ; 
 int /*<<< orphan*/  TIMER_GROUP_0 ; 
 int TIMER_INTR_T0 ; 
 int /*<<< orphan*/  esp_restart () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rtc_get_reset_reason (int /*<<< orphan*/ ) ; 
 int timer_group_intr_get_in_isr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_group_test_init () ; 
 int /*<<< orphan*/  timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void timer_group_test_first_stage(void)
{
    RESET_REASON rst_res = rtc_get_reset_reason(0);
    if(rst_res != POWERON_RESET){
        printf("Not power on reset\n");
    }
    TEST_ASSERT_EQUAL(POWERON_RESET, rst_res);
    static uint8_t loop_cnt = 0;
    timer_group_test_init();
    //Start timer
    timer_start(TIMER_GROUP_0, TIMER_0);
    //Waiting for timer_group to generate an interrupt
    while( !(timer_group_intr_get_in_isr(TIMER_GROUP_0) & TIMER_INTR_T0) &&
            loop_cnt++ < 100) {
        vTaskDelay(200);
    }
    //TIMERG0.int_raw.t0 == 1 means an interruption has occurred
    TEST_ASSERT(timer_group_intr_get_in_isr(TIMER_GROUP_0) & TIMER_INTR_T0);
    esp_restart();
}