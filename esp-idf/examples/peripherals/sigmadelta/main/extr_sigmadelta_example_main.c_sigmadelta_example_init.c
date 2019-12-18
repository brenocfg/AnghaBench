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
struct TYPE_3__ {int sigmadelta_prescale; int /*<<< orphan*/  sigmadelta_gpio; int /*<<< orphan*/  sigmadelta_duty; int /*<<< orphan*/  channel; } ;
typedef  TYPE_1__ sigmadelta_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_NUM_4 ; 
 int /*<<< orphan*/  SIGMADELTA_CHANNEL_0 ; 
 int /*<<< orphan*/  sigmadelta_config (TYPE_1__*) ; 

__attribute__((used)) static void sigmadelta_example_init(void)
{
    sigmadelta_config_t sigmadelta_cfg = {
        .channel = SIGMADELTA_CHANNEL_0,
        .sigmadelta_prescale = 80,
        .sigmadelta_duty = 0,
        .sigmadelta_gpio = GPIO_NUM_4,
    };
    sigmadelta_config(&sigmadelta_cfg);
}