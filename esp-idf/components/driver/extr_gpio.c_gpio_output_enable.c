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
typedef  int gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int data; } ;
struct TYPE_4__ {int enable_w1ts; TYPE_1__ enable1_w1ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ GPIO ; 
 int /*<<< orphan*/  GPIO_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_IS_VALID_OUTPUT_GPIO (int) ; 
 int /*<<< orphan*/  SIG_GPIO_OUT_IDX ; 
 int /*<<< orphan*/  gpio_matrix_out (int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static esp_err_t gpio_output_enable(gpio_num_t gpio_num)
{
    GPIO_CHECK(GPIO_IS_VALID_OUTPUT_GPIO(gpio_num), "GPIO output gpio_num error", ESP_ERR_INVALID_ARG);
    if (gpio_num < 32) {
        GPIO.enable_w1ts = (0x1 << gpio_num);
    } else {
        GPIO.enable1_w1ts.data = (0x1 << (gpio_num - 32));
    }
    gpio_matrix_out(gpio_num, SIG_GPIO_OUT_IDX, false, false);
    return ESP_OK;
}