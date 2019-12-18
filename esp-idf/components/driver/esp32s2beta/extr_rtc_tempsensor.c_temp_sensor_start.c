#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int tsens_power_up; scalar_t__ tsens_dump_out; } ;
struct TYPE_4__ {int tsens_clkgate_en; } ;
struct TYPE_6__ {TYPE_2__ sar_tctrl; TYPE_1__ sar_tctrl2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__ SENS ; 
 int /*<<< orphan*/  TSENS_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtc_tsens_mux ; 
 int /*<<< orphan*/ * xSemaphoreCreateMutex () ; 

esp_err_t temp_sensor_start(void)
{
    if (rtc_tsens_mux == NULL) {
        rtc_tsens_mux = xSemaphoreCreateMutex();
    }
    TSENS_CHECK(rtc_tsens_mux != NULL, ESP_ERR_NO_MEM);
    SENS.sar_tctrl.tsens_dump_out = 0;
    SENS.sar_tctrl2.tsens_clkgate_en = 1;
    SENS.sar_tctrl.tsens_power_up = 1;
    return ESP_OK;
}