#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int freq_mhz; } ;
typedef  TYPE_1__ rtc_cpu_freq_config_t ;

/* Variables and functions */
 int CONFIG_ESP_CONSOLE_UART_BAUDRATE ; 
 int CONFIG_ESP_CONSOLE_UART_NUM ; 
 int XT_TICK_PER_SEC ; 
 int _xt_tick_divisor ; 
 int /*<<< orphan*/  accessAPB ; 
 int /*<<< orphan*/  accessDPORT ; 
 int apb_test_result ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int dport_test_result ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int rtc_clk_apb_freq_get () ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_get_config (TYPE_1__*) ; 
 int rtc_clk_cpu_freq_mhz_to_config (int,TYPE_1__*) ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_set_config (TYPE_1__*) ; 
 int /*<<< orphan*/  run_tasks (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_div_modify (int const,int) ; 
 int /*<<< orphan*/  uart_tx_wait_idle (int const) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void run_tasks_with_change_freq_cpu(int cpu_freq_mhz)
{
    const int uart_num = CONFIG_ESP_CONSOLE_UART_NUM;
    const int uart_baud = CONFIG_ESP_CONSOLE_UART_BAUDRATE;
    dport_test_result = false;
    apb_test_result = false;
    rtc_cpu_freq_config_t old_config;
    rtc_clk_cpu_freq_get_config(&old_config);

    printf("CPU_FREQ = %d MHz\n", old_config.freq_mhz);

    if (cpu_freq_mhz != old_config.freq_mhz) {
        rtc_cpu_freq_config_t new_config;
        bool res = rtc_clk_cpu_freq_mhz_to_config(cpu_freq_mhz, &new_config);
        assert(res && "invalid frequency value");

        uart_tx_wait_idle(uart_num);
        rtc_clk_cpu_freq_set_config(&new_config);
        uart_div_modify(uart_num, (rtc_clk_apb_freq_get() << 4) / uart_baud);
        /* adjust RTOS ticks */
        _xt_tick_divisor = cpu_freq_mhz * 1000000 / XT_TICK_PER_SEC;
        vTaskDelay(2);

        printf("CPU_FREQ switched to %d MHz\n", cpu_freq_mhz);
    }
    run_tasks("accessDPORT", accessDPORT, "accessAPB", accessAPB, 10000);

    // return old freq.
    uart_tx_wait_idle(uart_num);
    rtc_clk_cpu_freq_set_config(&old_config);
    uart_div_modify(uart_num, (rtc_clk_apb_freq_get() << 4) / uart_baud);
    _xt_tick_divisor = old_config.freq_mhz * 1000000 / XT_TICK_PER_SEC;
}