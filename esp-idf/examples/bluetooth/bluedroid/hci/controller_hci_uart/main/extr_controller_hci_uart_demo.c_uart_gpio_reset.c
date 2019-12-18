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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_BT_HCI_UART_NO ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERIPH_UART1_MODULE ; 
 int /*<<< orphan*/  PERIPH_UART2_MODULE ; 
 int /*<<< orphan*/  PERIPH_UHCI0_MODULE ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tag ; 
 int /*<<< orphan*/  uart_set_pin (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void uart_gpio_reset(void)
{
#if CONFIG_BT_HCI_UART_NO == 1
    periph_module_enable(PERIPH_UART1_MODULE);
#elif CONFIG_BT_HCI_UART_NO == 2
    periph_module_enable(PERIPH_UART2_MODULE);
#endif
    periph_module_enable(PERIPH_UHCI0_MODULE);

#ifdef CONFIG_BT_HCI_UART_NO
    ESP_LOGI(tag, "HCI UART%d Pin select: TX 5, RX, 18, CTS 23, RTS 19", CONFIG_BT_HCI_UART_NO);

    uart_set_pin(CONFIG_BT_HCI_UART_NO, 5, 18, 19, 23);
#endif
}