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
struct TYPE_3__ {scalar_t__ t0; } ;
struct TYPE_4__ {TYPE_1__ int_raw; } ;
typedef  scalar_t__ RESET_REASON ;

/* Variables and functions */
 scalar_t__ SW_CPU_RESET ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (scalar_t__,scalar_t__) ; 
 TYPE_2__ TIMERG0 ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rtc_get_reset_reason (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_group_test_init () ; 

__attribute__((used)) static void timer_group_test_second_stage(void)
{
    RESET_REASON rst_res = rtc_get_reset_reason(0);
    if(rst_res != SW_CPU_RESET){
        printf("Not software reset\n");
    }
    TEST_ASSERT_EQUAL(SW_CPU_RESET, rst_res);
    timer_group_test_init();
    //After the timer_group is initialized, TIMERG0.int_raw.t0 should be cleared.
    TEST_ASSERT_EQUAL(0, TIMERG0.int_raw.t0);
}