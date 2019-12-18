#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  size_t gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {TYPE_1__* pin; } ;
struct TYPE_3__ {void* int_ena; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ GPIO ; 
 void* GPIO_APP_CPU_INTR_ENA ; 
 void* GPIO_PRO_CPU_INTR_ENA ; 
 int /*<<< orphan*/  gpio_intr_status_clr (size_t) ; 

__attribute__((used)) static esp_err_t gpio_intr_enable_on_core (gpio_num_t gpio_num, uint32_t core_id)
{
    gpio_intr_status_clr(gpio_num);
#if CONFIG_IDF_TARGET_ESP32
    if (core_id == 0) {
        GPIO.pin[gpio_num].int_ena = GPIO_PRO_CPU_INTR_ENA;     //enable pro cpu intr
    } else {
        GPIO.pin[gpio_num].int_ena = GPIO_APP_CPU_INTR_ENA;     //enable pro cpu intr
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    if (core_id == 0) {
        GPIO.pin[gpio_num].int_ena = GPIO_PRO_CPU_INTR_ENA;     //enable pro cpu intr
    }
#endif
    return ESP_OK;
}