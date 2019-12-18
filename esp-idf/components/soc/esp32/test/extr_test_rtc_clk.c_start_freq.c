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
typedef  long long uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ rtc_slow_freq_t ;

/* Variables and functions */
 int CONFIG_ESP32_RTC_CLK_CAL_CYCLES ; 
 int CONFIG_ESP32_RTC_XTAL_BOOTSTRAP_CYCLES ; 
 int COUNT_TEST ; 
 int /*<<< orphan*/  TEST_ASSERT_MESSAGE (int,char*) ; 
 int configTICK_RATE_HZ ; 
 long long esp_clk_rtc_time () ; 
 int esp_clk_slowclk_cal_get () ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rtc_clk_32k_bootstrap (int) ; 
 int /*<<< orphan*/  rtc_clk_select_rtc_slow_clk () ; 
 scalar_t__ rtc_clk_slow_freq_get () ; 
 int /*<<< orphan*/  stop_rtc_external_quartz () ; 
 int xTaskGetTickCount () ; 

__attribute__((used)) static void start_freq(rtc_slow_freq_t required_src_freq, uint32_t start_delay_ms)
{
    int i = 0, fail = 0;
    uint32_t start_time;
    uint32_t end_time;
    rtc_slow_freq_t selected_src_freq;
    stop_rtc_external_quartz();
#ifdef CONFIG_ESP32_RTC_CLK_SRC_EXT_CRYS
    uint32_t bootstrap_cycles = CONFIG_ESP32_RTC_XTAL_BOOTSTRAP_CYCLES;
    printf("Test is started. Kconfig settings:\n External 32K crystal is selected,\n Oscillation cycles = %d,\n Calibration cycles = %d.\n",
            bootstrap_cycles,
            CONFIG_ESP32_RTC_CLK_CAL_CYCLES);
#else
    uint32_t bootstrap_cycles = 5;
    printf("Test is started. Kconfig settings:\n Internal RC is selected,\n Oscillation cycles = %d,\n Calibration cycles = %d.\n",
            bootstrap_cycles,
            CONFIG_ESP32_RTC_CLK_CAL_CYCLES);
#endif
    if (start_delay_ms == 0 && CONFIG_ESP32_RTC_CLK_CAL_CYCLES < 1500){
        start_delay_ms = 50;
        printf("Recommended increase Number of cycles for RTC_SLOW_CLK calibration to 3000!\n");
    }
    while(i < COUNT_TEST){
        start_time = xTaskGetTickCount() * (1000 / configTICK_RATE_HZ);
        i++;
        printf("attempt #%d/%d...", i, COUNT_TEST);
        rtc_clk_32k_bootstrap(bootstrap_cycles);
        ets_delay_us(start_delay_ms * 1000);
        rtc_clk_select_rtc_slow_clk();
        selected_src_freq = rtc_clk_slow_freq_get();
        end_time = xTaskGetTickCount() * (1000 / configTICK_RATE_HZ);
        printf(" [time=%d] ", (end_time - start_time) - start_delay_ms);
        if(selected_src_freq != required_src_freq){
            printf("FAIL. Time measurement...");
            fail = 1;
        } else {
            printf("PASS. Time measurement...");
        }
        uint64_t clk_rtc_time;
        uint32_t fail_measure = 0;
        for (int j = 0; j < 3; ++j) {
            clk_rtc_time = esp_clk_rtc_time();
            ets_delay_us(1000000);
            uint64_t delta = esp_clk_rtc_time() - clk_rtc_time;
            if (delta < 900000LL || delta > 1100000){
                printf("FAIL");
                fail = 1;
                fail_measure = 1;
                break;
            }
        }
        if(fail_measure == 0) {
            printf("PASS");
        }
        printf(" [calibration val = %d] \n", esp_clk_slowclk_cal_get());
        stop_rtc_external_quartz();
        ets_delay_us(500000);
    }
    TEST_ASSERT_MESSAGE(fail == 0, "Test failed");
    printf("Test passed successfully\n");
}