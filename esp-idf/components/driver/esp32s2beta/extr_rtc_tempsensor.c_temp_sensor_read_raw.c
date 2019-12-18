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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int tsens_dump_out; int /*<<< orphan*/  tsens_out; int /*<<< orphan*/  tsens_ready; } ;
struct TYPE_4__ {TYPE_1__ sar_tctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ SENS ; 
 int /*<<< orphan*/  TSENS_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/ * rtc_tsens_mux ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

esp_err_t temp_sensor_read_raw(uint32_t *tsens_out)
{   
    TSENS_CHECK(tsens_out != NULL, ESP_ERR_INVALID_ARG);
    TSENS_CHECK(rtc_tsens_mux != NULL, ESP_ERR_INVALID_STATE);
    xSemaphoreTake(rtc_tsens_mux, portMAX_DELAY);
    SENS.sar_tctrl.tsens_dump_out = 1;
    while (!SENS.sar_tctrl.tsens_ready);
    *tsens_out = SENS.sar_tctrl.tsens_out;
    SENS.sar_tctrl.tsens_dump_out = 0;
    xSemaphoreGive(rtc_tsens_mux);
    return ESP_OK;
}