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
struct TYPE_3__ {int /*<<< orphan*/  mcpwm_cap2_in_num; int /*<<< orphan*/  mcpwm_cap1_in_num; int /*<<< orphan*/  mcpwm_cap0_in_num; int /*<<< orphan*/  mcpwm_fault2_in_num; int /*<<< orphan*/  mcpwm_fault1_in_num; int /*<<< orphan*/  mcpwm_fault0_in_num; int /*<<< orphan*/  mcpwm_sync2_in_num; int /*<<< orphan*/  mcpwm_sync1_in_num; int /*<<< orphan*/  mcpwm_sync0_in_num; int /*<<< orphan*/  mcpwm2b_out_num; int /*<<< orphan*/  mcpwm2a_out_num; int /*<<< orphan*/  mcpwm1b_out_num; int /*<<< orphan*/  mcpwm1a_out_num; int /*<<< orphan*/  mcpwm0b_out_num; int /*<<< orphan*/  mcpwm0a_out_num; } ;
typedef  TYPE_1__ mcpwm_pin_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CAP0_IN ; 
 int /*<<< orphan*/  GPIO_CAP1_IN ; 
 int /*<<< orphan*/  GPIO_CAP2_IN ; 
 int /*<<< orphan*/  GPIO_FAULT0_IN ; 
 int /*<<< orphan*/  GPIO_FAULT1_IN ; 
 int /*<<< orphan*/  GPIO_FAULT2_IN ; 
 int /*<<< orphan*/  GPIO_PWM0A_OUT ; 
 int /*<<< orphan*/  GPIO_PWM0B_OUT ; 
 int /*<<< orphan*/  GPIO_PWM1A_OUT ; 
 int /*<<< orphan*/  GPIO_PWM1B_OUT ; 
 int /*<<< orphan*/  GPIO_PWM2A_OUT ; 
 int /*<<< orphan*/  GPIO_PWM2B_OUT ; 
 int /*<<< orphan*/  GPIO_SYNC0_IN ; 
 int /*<<< orphan*/  GPIO_SYNC1_IN ; 
 int /*<<< orphan*/  GPIO_SYNC2_IN ; 
 int /*<<< orphan*/  MCPWM0A ; 
 int /*<<< orphan*/  MCPWM0B ; 
 int /*<<< orphan*/  MCPWM1A ; 
 int /*<<< orphan*/  MCPWM1B ; 
 int /*<<< orphan*/  MCPWM2A ; 
 int /*<<< orphan*/  MCPWM2B ; 
 int /*<<< orphan*/  MCPWM_CAP_0 ; 
 int /*<<< orphan*/  MCPWM_CAP_1 ; 
 int /*<<< orphan*/  MCPWM_CAP_2 ; 
 int /*<<< orphan*/  MCPWM_FAULT_0 ; 
 int /*<<< orphan*/  MCPWM_FAULT_1 ; 
 int /*<<< orphan*/  MCPWM_FAULT_2 ; 
 int /*<<< orphan*/  MCPWM_SYNC_0 ; 
 int /*<<< orphan*/  MCPWM_SYNC_1 ; 
 int /*<<< orphan*/  MCPWM_SYNC_2 ; 
 int /*<<< orphan*/  MCPWM_UNIT_0 ; 
 int /*<<< orphan*/  gpio_pulldown_en (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_gpio_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_set_pin (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void mcpwm_example_gpio_initialize(void)
{
    printf("initializing mcpwm gpio...\n");
#if MCPWM_GPIO_INIT
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, GPIO_PWM1A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, GPIO_PWM1B_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2A, GPIO_PWM2A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2B, GPIO_PWM2B_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, GPIO_CAP0_IN);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_1, GPIO_CAP1_IN);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_2, GPIO_CAP2_IN);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_SYNC_0, GPIO_SYNC0_IN);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_SYNC_1, GPIO_SYNC1_IN);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_SYNC_2, GPIO_SYNC2_IN);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_FAULT_0, GPIO_FAULT0_IN);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_FAULT_1, GPIO_FAULT1_IN);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_FAULT_2, GPIO_FAULT2_IN);
#else
    mcpwm_pin_config_t pin_config = {
        .mcpwm0a_out_num = GPIO_PWM0A_OUT,
        .mcpwm0b_out_num = GPIO_PWM0B_OUT,
        .mcpwm1a_out_num = GPIO_PWM1A_OUT,
        .mcpwm1b_out_num = GPIO_PWM1B_OUT,
        .mcpwm2a_out_num = GPIO_PWM2A_OUT,
        .mcpwm2b_out_num = GPIO_PWM2B_OUT,
        .mcpwm_sync0_in_num  = GPIO_SYNC0_IN,
        .mcpwm_sync1_in_num  = GPIO_SYNC1_IN,
        .mcpwm_sync2_in_num  = GPIO_SYNC2_IN,
        .mcpwm_fault0_in_num = GPIO_FAULT0_IN,
        .mcpwm_fault1_in_num = GPIO_FAULT1_IN,
        .mcpwm_fault2_in_num = GPIO_FAULT2_IN,
        .mcpwm_cap0_in_num   = GPIO_CAP0_IN,
        .mcpwm_cap1_in_num   = GPIO_CAP1_IN,
        .mcpwm_cap2_in_num   = GPIO_CAP2_IN
    };
    mcpwm_set_pin(MCPWM_UNIT_0, &pin_config);
#endif
    gpio_pulldown_en(GPIO_CAP0_IN);    //Enable pull down on CAP0   signal
    gpio_pulldown_en(GPIO_CAP1_IN);    //Enable pull down on CAP1   signal
    gpio_pulldown_en(GPIO_CAP2_IN);    //Enable pull down on CAP2   signal
    gpio_pulldown_en(GPIO_SYNC0_IN);   //Enable pull down on SYNC0  signal
    gpio_pulldown_en(GPIO_SYNC1_IN);   //Enable pull down on SYNC1  signal
    gpio_pulldown_en(GPIO_SYNC2_IN);   //Enable pull down on SYNC2  signal
    gpio_pulldown_en(GPIO_FAULT0_IN);  //Enable pull down on FAULT0 signal
    gpio_pulldown_en(GPIO_FAULT1_IN);  //Enable pull down on FAULT1 signal
    gpio_pulldown_en(GPIO_FAULT2_IN);  //Enable pull down on FAULT2 signal
}