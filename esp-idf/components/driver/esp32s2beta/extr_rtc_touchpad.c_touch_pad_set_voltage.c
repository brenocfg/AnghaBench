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
typedef  scalar_t__ touch_volt_atten_t ;
typedef  scalar_t__ touch_low_volt_t ;
typedef  scalar_t__ touch_high_volt_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {scalar_t__ touch_drange; scalar_t__ touch_drefl; scalar_t__ touch_drefh; } ;
struct TYPE_4__ {TYPE_1__ touch_ctrl2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RTCCNTL ; 
 int /*<<< orphan*/  RTC_TOUCH_ENTER_CRITICAL () ; 
 int /*<<< orphan*/  RTC_TOUCH_EXIT_CRITICAL () ; 
 scalar_t__ TOUCH_HVOLT_ATTEN_KEEP ; 
 scalar_t__ TOUCH_HVOLT_KEEP ; 
 scalar_t__ TOUCH_LVOLT_KEEP ; 

esp_err_t touch_pad_set_voltage(touch_high_volt_t refh, touch_low_volt_t refl, touch_volt_atten_t atten)
{
    RTC_TOUCH_ENTER_CRITICAL();
    if (refh > TOUCH_HVOLT_KEEP) {
        RTCCNTL.touch_ctrl2.touch_drefh = refh;
    }
    if (refl > TOUCH_LVOLT_KEEP) {
        RTCCNTL.touch_ctrl2.touch_drefl = refl;
    }
    if (atten > TOUCH_HVOLT_ATTEN_KEEP) {
        RTCCNTL.touch_ctrl2.touch_drange = atten;
    }
    RTC_TOUCH_EXIT_CRITICAL();
    return ESP_OK;
}