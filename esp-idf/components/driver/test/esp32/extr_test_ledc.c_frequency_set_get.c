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
typedef  int /*<<< orphan*/  ledc_timer_t ;
typedef  int /*<<< orphan*/  ledc_mode_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_INT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_INT16_WITHIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledc_get_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledc_set_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wave_count (int) ; 

__attribute__((used)) static void frequency_set_get(ledc_mode_t speed_mode, ledc_timer_t timer, uint32_t freq_hz, int16_t real_freq, int16_t error)
{
    int16_t count;
    TEST_ESP_OK(ledc_set_freq(speed_mode, timer, freq_hz));
    count = wave_count(1000);
    TEST_ASSERT_INT16_WITHIN(error, count, real_freq);
    TEST_ASSERT_EQUAL_INT32(ledc_get_freq(speed_mode, timer), real_freq);
}