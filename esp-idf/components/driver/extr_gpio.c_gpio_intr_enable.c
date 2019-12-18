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
typedef  int /*<<< orphan*/  gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  GPIO_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ GPIO_ISR_CORE_ID_UNINIT ; 
 int /*<<< orphan*/  GPIO_IS_VALID_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_intr_enable_on_core (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gpio_spinlock ; 
 scalar_t__ isr_core_id ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 scalar_t__ xPortGetCoreID () ; 

esp_err_t gpio_intr_enable(gpio_num_t gpio_num)
{
    GPIO_CHECK(GPIO_IS_VALID_GPIO(gpio_num), "GPIO number error", ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&gpio_spinlock);
    if(isr_core_id == GPIO_ISR_CORE_ID_UNINIT) {
        isr_core_id = xPortGetCoreID();
    }
    portEXIT_CRITICAL(&gpio_spinlock);
    return gpio_intr_enable_on_core (gpio_num, isr_core_id);
}