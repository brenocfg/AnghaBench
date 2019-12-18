#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int cpu_freq_mhz; int /*<<< orphan*/  fast_freq; int /*<<< orphan*/  slow_freq; int /*<<< orphan*/  cpu_freq; int /*<<< orphan*/  xtal_freq; } ;
typedef  TYPE_1__ rtc_clk_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ESP32S2_XTAL_FREQ ; 
 int /*<<< orphan*/  CONFIG_ESP32_RTC_XTAL_BOOTSTRAP_CYCLES ; 
 int /*<<< orphan*/  CONFIG_ESP32_XTAL_FREQ ; 
 int /*<<< orphan*/  DPORT_CPUPERIOD_SEL ; 
 scalar_t__ DPORT_CPUPERIOD_SEL_240 ; 
 int /*<<< orphan*/  DPORT_CPU_PER_CONF_REG ; 
 scalar_t__ DPORT_REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFUSE_BLK0_RDATA3_REG ; 
 int EFUSE_RD_CHIP_VER_REV1_M ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__ RTC_CLK_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  RTC_CPU_FREQ_80M ; 
 int /*<<< orphan*/  rtc_clk_32k_bootstrap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_32k_enabled () ; 
 int /*<<< orphan*/  rtc_clk_fast_freq_get () ; 
 int /*<<< orphan*/  rtc_clk_init (TYPE_1__) ; 
 int /*<<< orphan*/  rtc_clk_slow_freq_get () ; 
 int /*<<< orphan*/  uart_tx_wait_idle (int /*<<< orphan*/ ) ; 

void bootloader_clock_configure(void)
{
    // ROM bootloader may have put a lot of text into UART0 FIFO.
    // Wait for it to be printed.
    // This is not needed on power on reset, when ROM bootloader is running at
    // 40 MHz. But in case of TG WDT reset, CPU may still be running at >80 MHZ,
    // and will be done with the bootloader much earlier than UART FIFO is empty.
    uart_tx_wait_idle(0);

    /* On ESP32 rev 0, switching to 80/160 MHz if clock was previously set to
     * 240 MHz may cause the chip to lock up (see section 3.5 of the errata
     * document). For rev. 0, switch to 240 instead if it has been enabled
     * previously.
     */
#if CONFIG_IDF_TARGET_ESP32
    /* Set CPU to 80MHz. Keep other clocks unmodified. */
    int cpu_freq_mhz = 80;

    uint32_t chip_ver_reg = REG_READ(EFUSE_BLK0_RDATA3_REG);
    if ((chip_ver_reg & EFUSE_RD_CHIP_VER_REV1_M) == 0 &&
            DPORT_REG_GET_FIELD(DPORT_CPU_PER_CONF_REG, DPORT_CPUPERIOD_SEL) == DPORT_CPUPERIOD_SEL_240) {
        cpu_freq_mhz = 240;
    }
#endif

    rtc_clk_config_t clk_cfg = RTC_CLK_CONFIG_DEFAULT();
#if CONFIG_IDF_TARGET_ESP32
    clk_cfg.xtal_freq = CONFIG_ESP32_XTAL_FREQ;
    clk_cfg.cpu_freq_mhz = cpu_freq_mhz;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    clk_cfg.xtal_freq = CONFIG_ESP32S2_XTAL_FREQ;
    clk_cfg.cpu_freq = RTC_CPU_FREQ_80M;
#endif
    clk_cfg.slow_freq = rtc_clk_slow_freq_get();
    clk_cfg.fast_freq = rtc_clk_fast_freq_get();
    rtc_clk_init(clk_cfg);
    /* As a slight optimization, if 32k XTAL was enabled in sdkconfig, we enable
     * it here. Usually it needs some time to start up, so we amortize at least
     * part of the start up time by enabling 32k XTAL early.
     * App startup code will wait until the oscillator has started up.
     */
#ifdef CONFIG_ESP32_RTC_CLK_SRC_EXT_CRYS
    if (!rtc_clk_32k_enabled()) {
        rtc_clk_32k_bootstrap(CONFIG_ESP32_RTC_XTAL_BOOTSTRAP_CYCLES);
    }
#endif
}