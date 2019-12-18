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
struct TYPE_3__ {int /*<<< orphan*/  cap_level; int /*<<< orphan*/  grade; } ;
typedef  TYPE_1__ touch_pad_denoise_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int TOUCH_BUTTON_NUM ; 
 int /*<<< orphan*/  TOUCH_FSM_MODE_TIMER ; 
 int /*<<< orphan*/  TOUCH_PAD_DENOISE_BIT4 ; 
 int /*<<< orphan*/  TOUCH_PAD_DENOISE_CAP_L7 ; 
 int /*<<< orphan*/  TOUCH_PAD_THRESHOLD_MAX ; 
 int /*<<< orphan*/ * button ; 
 int /*<<< orphan*/  touch_pad_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_pad_denoise_enable () ; 
 int /*<<< orphan*/  touch_pad_denoise_set_config (TYPE_1__) ; 
 int /*<<< orphan*/  touch_pad_fsm_start () ; 
 int /*<<< orphan*/  touch_pad_init () ; 
 int /*<<< orphan*/  touch_pad_set_fsm_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_pad_set_thresh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_example_read_task ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void app_main(void)
{
    /* Initialize touch pad peripheral. */
    touch_pad_init();
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        touch_pad_config(button[i]);
        touch_pad_set_thresh(button[i], TOUCH_PAD_THRESHOLD_MAX);
    }

    /* Denoise setting at TouchSensor 0. */
    touch_pad_denoise_t denoise = {
            /* The bits to be cancelled are determined according to the noise level. */
            .grade = TOUCH_PAD_DENOISE_BIT4,    
            .cap_level = TOUCH_PAD_DENOISE_CAP_L7,
    };
    touch_pad_denoise_set_config(denoise);
    touch_pad_denoise_enable();
    ESP_LOGI(TAG, "Denoise function init");

    /* Enable touch sensor clock. Work mode is "timer trigger". */
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    touch_pad_fsm_start();
    
    /* Start task to read values by pads. */
    xTaskCreate(&tp_example_read_task, "touch_pad_read_task", 2048, NULL, 5, NULL);
}