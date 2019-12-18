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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  rtc_cpu_freq_t ;
typedef  int /*<<< orphan*/  rtc_config_t ;

/* Variables and functions */
 int CONFIG_BOOTLOADER_WDT_TIME_MS ; 
 int CONFIG_ESP32S2_DEFAULT_CPU_FREQ_MHZ ; 
 int /*<<< orphan*/  CONFIG_ESP_CONSOLE_UART_NUM ; 
 int MHZ ; 
 int /*<<< orphan*/  RTC_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  RTC_CPU_FREQ_160M ; 
 int /*<<< orphan*/  RTC_CPU_FREQ_240M ; 
 int /*<<< orphan*/  RTC_CPU_FREQ_80M ; 
 int /*<<< orphan*/  RTC_FAST_FREQ_8M ; 
 int /*<<< orphan*/  RTC_SLOW_FREQ_32K_XTAL ; 
 int /*<<< orphan*/  RTC_SLOW_FREQ_RTC ; 
 int /*<<< orphan*/  RTC_WDT_STAGE0 ; 
 scalar_t__ RTC_XTAL_FREQ_AUTO ; 
 int XTHAL_GET_CCOUNT () ; 
 int /*<<< orphan*/  XTHAL_SET_CCOUNT (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_get () ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_set (int /*<<< orphan*/ ) ; 
 int rtc_clk_cpu_freq_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_fast_freq_set (int /*<<< orphan*/ ) ; 
 scalar_t__ rtc_clk_xtal_freq_get () ; 
 int /*<<< orphan*/  rtc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_wdt_feed () ; 
 int /*<<< orphan*/  rtc_wdt_protect_off () ; 
 int /*<<< orphan*/  rtc_wdt_protect_on () ; 
 int /*<<< orphan*/  rtc_wdt_set_time (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  select_rtc_slow_clk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_tx_wait_idle (int /*<<< orphan*/ ) ; 

void esp_clk_init(void)
{
    rtc_config_t cfg = RTC_CONFIG_DEFAULT();
    rtc_init(cfg);

    assert(rtc_clk_xtal_freq_get() != RTC_XTAL_FREQ_AUTO);

    rtc_clk_fast_freq_set(RTC_FAST_FREQ_8M);

#ifdef CONFIG_BOOTLOADER_WDT_ENABLE
    // WDT uses a SLOW_CLK clock source. After a function select_rtc_slow_clk a frequency of this source can changed.
    // If the frequency changes from 90kHz to 32kHz, then the timeout set for the WDT will increase 2.8 times.
    // Therefore, for the time of frequency change, set a new lower timeout value (1.6 sec).
    // This prevents excessive delay before resetting in case the supply voltage is drawdown.
    // (If frequency is changed from 90kHz to 32kHz then WDT timeout will increased to 1.6sec * 90/32 = 4.5 sec).
    rtc_wdt_protect_off();
    rtc_wdt_feed();
    rtc_wdt_set_time(RTC_WDT_STAGE0, 1600);
    rtc_wdt_protect_on();
#endif

#ifdef CONFIG_ESP32S2_RTC_CLK_SRC_EXT_CRYS
    select_rtc_slow_clk(RTC_SLOW_FREQ_32K_XTAL);
#else
    select_rtc_slow_clk(RTC_SLOW_FREQ_RTC);
#endif

#ifdef CONFIG_BOOTLOADER_WDT_ENABLE
    // After changing a frequency WDT timeout needs to be set for new frequency.
    rtc_wdt_protect_off();
    rtc_wdt_feed();
    rtc_wdt_set_time(RTC_WDT_STAGE0, CONFIG_BOOTLOADER_WDT_TIME_MS);
    rtc_wdt_protect_on();
#endif

    uint32_t freq_mhz = CONFIG_ESP32S2_DEFAULT_CPU_FREQ_MHZ;
    rtc_cpu_freq_t freq = RTC_CPU_FREQ_80M;
    switch(freq_mhz) {
        case 240:
            freq = RTC_CPU_FREQ_240M;
            break;
        case 160:
            freq = RTC_CPU_FREQ_160M;
            break;
        case 80:
            freq = RTC_CPU_FREQ_80M;
            break;
        default:
            freq_mhz = 80;
            freq = RTC_CPU_FREQ_80M;
            break;
    }

    // Wait for UART TX to finish, otherwise some UART output will be lost
    // when switching APB frequency
    uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);

    uint32_t freq_before = rtc_clk_cpu_freq_value(rtc_clk_cpu_freq_get()) / MHZ ;

    rtc_clk_cpu_freq_set(freq);

    // Re calculate the ccount to make time calculation correct.
    uint32_t freq_after = CONFIG_ESP32S2_DEFAULT_CPU_FREQ_MHZ;
    XTHAL_SET_CCOUNT( XTHAL_GET_CCOUNT() * freq_after / freq_before );
}