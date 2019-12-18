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
typedef  int /*<<< orphan*/  touch_fsm_mode_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  touch_start_force; } ;
struct TYPE_4__ {TYPE_1__ touch_ctrl2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RTCCNTL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

esp_err_t touch_pad_get_fsm_mode(touch_fsm_mode_t *mode)
{
    assert(mode != NULL);
    *mode = RTCCNTL.touch_ctrl2.touch_start_force;
    return ESP_OK;
}