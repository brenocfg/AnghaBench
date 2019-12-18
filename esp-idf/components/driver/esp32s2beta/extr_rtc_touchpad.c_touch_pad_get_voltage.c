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
typedef  int /*<<< orphan*/  touch_volt_atten_t ;
typedef  int /*<<< orphan*/  touch_low_volt_t ;
typedef  int /*<<< orphan*/  touch_high_volt_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  touch_drange; int /*<<< orphan*/  touch_drefl; int /*<<< orphan*/  touch_drefh; } ;
struct TYPE_4__ {TYPE_1__ touch_ctrl2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RTCCNTL ; 

esp_err_t touch_pad_get_voltage(touch_high_volt_t *refh, touch_low_volt_t *refl, touch_volt_atten_t *atten)
{
    if (refh) {
        *refh = RTCCNTL.touch_ctrl2.touch_drefh;
    }
    if (refl) {
        *refl = RTCCNTL.touch_ctrl2.touch_drefl;
    }
    if (atten) {
        *atten = RTCCNTL.touch_ctrl2.touch_drange;
    }
    return ESP_OK;
}