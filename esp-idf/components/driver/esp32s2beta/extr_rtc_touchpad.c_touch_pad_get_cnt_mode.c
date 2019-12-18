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
typedef  int /*<<< orphan*/  touch_tie_opt_t ;
typedef  size_t touch_pad_t ;
typedef  int /*<<< orphan*/  touch_cnt_slope_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {TYPE_1__* touch_pad; } ;
struct TYPE_3__ {int /*<<< orphan*/  tie_opt; int /*<<< orphan*/  dac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RTCIO ; 

esp_err_t touch_pad_get_cnt_mode(touch_pad_t touch_num, touch_cnt_slope_t *slope, touch_tie_opt_t *opt)
{
    if (slope) {
        *slope = RTCIO.touch_pad[touch_num].dac;
    }
    if (opt) {
        *opt = RTCIO.touch_pad[touch_num].tie_opt;
    }
    return ESP_OK;
}