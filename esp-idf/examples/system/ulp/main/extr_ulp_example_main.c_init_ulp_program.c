#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  rtc_num; scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 size_t GPIO_NUM_0 ; 
 int /*<<< orphan*/  GPIO_NUM_12 ; 
 int /*<<< orphan*/  GPIO_NUM_15 ; 
 int /*<<< orphan*/  RTC_GPIO_MODE_INPUT_ONLY ; 
 int RTC_SLOW_MEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  esp_deep_sleep_disable_rom_logging () ; 
 TYPE_1__* rtc_gpio_desc ; 
 int /*<<< orphan*/  rtc_gpio_hold_en (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_init (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_isolate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_pulldown_dis (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_pullup_dis (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_set_direction (size_t,int /*<<< orphan*/ ) ; 
 int ulp_debounce_counter ; 
 int ulp_debounce_max_count ; 
 int ulp_edge_count_to_wake_up ; 
 int /*<<< orphan*/  ulp_entry ; 
 int /*<<< orphan*/  ulp_io_number ; 
 int /*<<< orphan*/  ulp_load_binary (int /*<<< orphan*/ ,int,int) ; 
 int ulp_main_bin_end ; 
 int ulp_main_bin_start ; 
 scalar_t__ ulp_next_edge ; 
 int /*<<< orphan*/  ulp_run (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ulp_set_wakeup_period (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_ulp_program(void)
{
    esp_err_t err = ulp_load_binary(0, ulp_main_bin_start,
            (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));
    ESP_ERROR_CHECK(err);

    /* GPIO used for pulse counting. */
    gpio_num_t gpio_num = GPIO_NUM_0;
    assert(rtc_gpio_desc[gpio_num].reg && "GPIO used for pulse counting must be an RTC IO");

    /* Initialize some variables used by ULP program.
     * Each 'ulp_xyz' variable corresponds to 'xyz' variable in the ULP program.
     * These variables are declared in an auto generated header file,
     * 'ulp_main.h', name of this file is defined in component.mk as ULP_APP_NAME.
     * These variables are located in RTC_SLOW_MEM and can be accessed both by the
     * ULP and the main CPUs.
     *
     * Note that the ULP reads only the lower 16 bits of these variables.
     */
    ulp_debounce_counter = 3;
    ulp_debounce_max_count = 3;
    ulp_next_edge = 0;
    ulp_io_number = rtc_gpio_desc[gpio_num].rtc_num; /* map from GPIO# to RTC_IO# */
    ulp_edge_count_to_wake_up = 10;

    /* Initialize selected GPIO as RTC IO, enable input, disable pullup and pulldown */
    rtc_gpio_init(gpio_num);
    rtc_gpio_set_direction(gpio_num, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pulldown_dis(gpio_num);
    rtc_gpio_pullup_dis(gpio_num);
    rtc_gpio_hold_en(gpio_num);

    /* Disconnect GPIO12 and GPIO15 to remove current drain through
     * pullup/pulldown resistors.
     * GPIO12 may be pulled high to select flash voltage.
     */
    rtc_gpio_isolate(GPIO_NUM_12);
    rtc_gpio_isolate(GPIO_NUM_15);
    esp_deep_sleep_disable_rom_logging(); // suppress boot messages

    /* Set ULP wake up period to T = 20ms.
     * Minimum pulse width has to be T * (ulp_debounce_counter + 1) = 80ms.
     */
    ulp_set_wakeup_period(0, 20000);

    /* Start the program */
    err = ulp_run(&ulp_entry - RTC_SLOW_MEM);
    ESP_ERROR_CHECK(err);
}