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
typedef  size_t gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {scalar_t__ pullup; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int rue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 TYPE_2__* rtc_gpio_desc ; 
 TYPE_1__** rtc_gpio_reg ; 
 int /*<<< orphan*/  rtc_spinlock ; 

esp_err_t rtc_gpio_pullup_dis(gpio_num_t gpio_num)
{
#if CONFIG_IDF_TARGET_ESP32
    //this is a digital pad
    if ( rtc_gpio_desc[gpio_num].pullup == 0 ) {
        return ESP_ERR_INVALID_ARG;
    }

    //this is a rtc pad
    portENTER_CRITICAL(&rtc_spinlock);
    CLEAR_PERI_REG_MASK(rtc_gpio_desc[gpio_num].reg, rtc_gpio_desc[gpio_num].pullup);
    portEXIT_CRITICAL(&rtc_spinlock);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    portENTER_CRITICAL(&rtc_spinlock);
    rtc_gpio_reg[gpio_num]->rue = 0x0;
    portEXIT_CRITICAL(&rtc_spinlock);
#endif
    return ESP_OK;
}