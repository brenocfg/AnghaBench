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
struct TYPE_3__ {int pull_up_en; scalar_t__ pull_down_en; int /*<<< orphan*/  mode; int /*<<< orphan*/  pin_bit_mask; int /*<<< orphan*/  intr_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXAMPLE_BUTTON_GPIO ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 int /*<<< orphan*/  GPIO_PIN_INTR_DISABLE ; 
 int /*<<< orphan*/  gpio_config (TYPE_1__*) ; 

__attribute__((used)) static void initialise_button(void)
{
    gpio_config_t io_conf = {0};
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.pin_bit_mask = BIT64(EXAMPLE_BUTTON_GPIO);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    io_conf.pull_down_en = 0;
    gpio_config(&io_conf);
}