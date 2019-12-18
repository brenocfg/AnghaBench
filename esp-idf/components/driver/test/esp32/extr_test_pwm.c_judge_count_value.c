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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PWMA_PCNT_INPUT ; 
 int /*<<< orphan*/  GPIO_PWMB_PCNT_INPUT ; 
 int /*<<< orphan*/  PCNT_CTRL_FLOATING_IO1 ; 
 int /*<<< orphan*/  PCNT_CTRL_FLOATING_IO2 ; 
 int /*<<< orphan*/  TEST_ASSERT_INT16_WITHIN (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcnt_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void judge_count_value(int allow_error ,int expect_freq)
{
    int16_t countA, countB;

    countA = pcnt_count(GPIO_PWMA_PCNT_INPUT, PCNT_CTRL_FLOATING_IO1, 1000);
    countB = pcnt_count(GPIO_PWMB_PCNT_INPUT, PCNT_CTRL_FLOATING_IO2, 1000);

    TEST_ASSERT_INT16_WITHIN(allow_error, countA, expect_freq);
    TEST_ASSERT_INT16_WITHIN(allow_error, countB, expect_freq);
}