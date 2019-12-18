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
typedef  int /*<<< orphan*/  TimerHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_UINT32_WITHIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TICK_DELTA ; 
 int /*<<< orphan*/  tmr_ideal_exp ; 
 int /*<<< orphan*/  xTaskGetTickCount () ; 

__attribute__((used)) static void tmr_cb(TimerHandle_t xtimer)
{
    //Check cb is called in timely fashion
    TEST_ASSERT_UINT32_WITHIN(TICK_DELTA, tmr_ideal_exp, xTaskGetTickCount());
}