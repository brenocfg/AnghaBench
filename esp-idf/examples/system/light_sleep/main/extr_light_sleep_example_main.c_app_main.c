#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  pin_bit_mask; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT64 (int const) ; 
 int BUTTON_GPIO_NUM_DEFAULT ; 
 int BUTTON_WAKEUP_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  CONFIG_ESP_CONSOLE_UART_NUM ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
#define  ESP_SLEEP_WAKEUP_GPIO 129 
#define  ESP_SLEEP_WAKEUP_TIMER 128 
 int /*<<< orphan*/  GPIO_INTR_HIGH_LEVEL ; 
 int /*<<< orphan*/  GPIO_INTR_LOW_LEVEL ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 int /*<<< orphan*/  esp_light_sleep_start () ; 
 int /*<<< orphan*/  esp_sleep_enable_gpio_wakeup () ; 
 int /*<<< orphan*/  esp_sleep_enable_timer_wakeup (int) ; 
 int esp_sleep_get_wakeup_cause () ; 
 int esp_timer_get_time () ; 
 int /*<<< orphan*/  gpio_config (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_wakeup_enable (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int const rtc_gpio_get_level (int const) ; 
 int /*<<< orphan*/  uart_wait_tx_idle_polling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 

void app_main(void)
{
    /* Configure the button GPIO as input, enable wakeup */
    const int button_gpio_num = BUTTON_GPIO_NUM_DEFAULT;
    const int wakeup_level = BUTTON_WAKEUP_LEVEL_DEFAULT;
    gpio_config_t config = {
            .pin_bit_mask = BIT64(button_gpio_num),
            .mode = GPIO_MODE_INPUT
    };
    ESP_ERROR_CHECK(gpio_config(&config));
    gpio_wakeup_enable(button_gpio_num,
            wakeup_level == 0 ? GPIO_INTR_LOW_LEVEL : GPIO_INTR_HIGH_LEVEL);

    while (true) {
        /* Wake up in 2 seconds, or when button is pressed */
        esp_sleep_enable_timer_wakeup(2000000);
        esp_sleep_enable_gpio_wakeup();

        /* Wait until GPIO goes high */
        if (rtc_gpio_get_level(button_gpio_num) == wakeup_level) {
            printf("Waiting for GPIO%d to go high...\n", button_gpio_num);
            do {
                vTaskDelay(pdMS_TO_TICKS(10));
            } while (rtc_gpio_get_level(button_gpio_num) == wakeup_level);
        }

        printf("Entering light sleep\n");
        /* To make sure the complete line is printed before entering sleep mode,
         * need to wait until UART TX FIFO is empty:
         */
        uart_wait_tx_idle_polling(CONFIG_ESP_CONSOLE_UART_NUM);

        /* Get timestamp before entering sleep */
        int64_t t_before_us = esp_timer_get_time();

        /* Enter sleep mode */
        esp_light_sleep_start();
        /* Execution continues here after wakeup */

        /* Get timestamp after waking up from sleep */
        int64_t t_after_us = esp_timer_get_time();

        /* Determine wake up reason */
        const char* wakeup_reason;
        switch (esp_sleep_get_wakeup_cause()) {
            case ESP_SLEEP_WAKEUP_TIMER:
                wakeup_reason = "timer";
                break;
            case ESP_SLEEP_WAKEUP_GPIO:
                wakeup_reason = "pin";
                break;
            default:
                wakeup_reason = "other";
                break;
        }

        printf("Returned from light sleep, reason: %s, t=%lld ms, slept for %lld ms\n",
                wakeup_reason, t_after_us / 1000, (t_after_us - t_before_us) / 1000);
    }

}