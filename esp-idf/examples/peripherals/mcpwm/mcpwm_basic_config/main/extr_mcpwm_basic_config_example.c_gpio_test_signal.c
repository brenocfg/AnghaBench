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
struct TYPE_3__ {int /*<<< orphan*/  pin_bit_mask; int /*<<< orphan*/  mode; int /*<<< orphan*/  intr_type; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_INTR_DISABLE ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int /*<<< orphan*/  GPIO_NUM_12 ; 
 int /*<<< orphan*/  GPIO_SEL_12 ; 
 int /*<<< orphan*/  gpio_config (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_set_level (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void gpio_test_signal(void *arg)
{
    printf("intializing test signal...\n");
    gpio_config_t gp;
    gp.intr_type = GPIO_INTR_DISABLE;
    gp.mode = GPIO_MODE_OUTPUT;
    gp.pin_bit_mask = GPIO_SEL_12;
    gpio_config(&gp);
    while (1) {
        //here the period of test signal is 20ms
        gpio_set_level(GPIO_NUM_12, 1); //Set high
        vTaskDelay(10);             //delay of 10ms
        gpio_set_level(GPIO_NUM_12, 0); //Set low
        vTaskDelay(10);         //delay of 10ms
    }
}