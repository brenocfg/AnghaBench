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
struct TYPE_3__ {int pulse_gpio_num; int ctrl_gpio_num; int /*<<< orphan*/  counter_l_lim; int /*<<< orphan*/  counter_h_lim; int /*<<< orphan*/  hctrl_mode; int /*<<< orphan*/  lctrl_mode; int /*<<< orphan*/  neg_mode; int /*<<< orphan*/  pos_mode; int /*<<< orphan*/  unit; int /*<<< orphan*/  channel; } ;
typedef  TYPE_1__ pcnt_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  HIGHEST_LIMIT ; 
 int /*<<< orphan*/  LOWEST_LIMIT ; 
 int /*<<< orphan*/  PCNT_CHANNEL_0 ; 
 int /*<<< orphan*/  PCNT_COUNT_DIS ; 
 int /*<<< orphan*/  PCNT_COUNT_INC ; 
 int /*<<< orphan*/  PCNT_MODE_KEEP ; 
 int /*<<< orphan*/  PCNT_MODE_REVERSE ; 
 int /*<<< orphan*/  PCNT_UNIT_0 ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcnt_unit_config (TYPE_1__*) ; 

__attribute__((used)) static void pcnt_init(int pulse_gpio_num, int ctrl_gpio_num)
{
    pcnt_config_t pcnt_config = {
       .pulse_gpio_num = pulse_gpio_num,
       .ctrl_gpio_num = ctrl_gpio_num,
       .channel = PCNT_CHANNEL_0,
       .unit = PCNT_UNIT_0,
       .pos_mode = PCNT_COUNT_INC,
       .neg_mode = PCNT_COUNT_DIS,
       .lctrl_mode = PCNT_MODE_REVERSE,
       .hctrl_mode = PCNT_MODE_KEEP,
       .counter_h_lim = HIGHEST_LIMIT,
       .counter_l_lim = LOWEST_LIMIT,
   };
   TEST_ESP_OK(pcnt_unit_config(&pcnt_config));
}