#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int data; } ;
struct TYPE_4__ {int data; } ;
struct TYPE_6__ {int out_w1ts; int out_w1tc; TYPE_2__ out1_w1tc; TYPE_1__ out1_w1ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__ GPIO ; 
 int /*<<< orphan*/  GPIO_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_IS_VALID_OUTPUT_GPIO (int) ; 

esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
{
    GPIO_CHECK(GPIO_IS_VALID_OUTPUT_GPIO(gpio_num), "GPIO output gpio_num error", ESP_ERR_INVALID_ARG);
    if (level) {
        if (gpio_num < 32) {
            GPIO.out_w1ts = (1 << gpio_num);
        } else {
            GPIO.out1_w1ts.data = (1 << (gpio_num - 32));
        }
    } else {
        if (gpio_num < 32) {
            GPIO.out_w1tc = (1 << gpio_num);
        } else {
            GPIO.out1_w1tc.data = (1 << (gpio_num - 32));
        }
    }
    return ESP_OK;
}