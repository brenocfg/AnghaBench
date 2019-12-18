#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t dac_offset; int /*<<< orphan*/  clk_div; } ;
typedef  TYPE_3__ temp_sensor_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int tsens_xpd_force; int tsens_reset; int /*<<< orphan*/  tsens_xpd_wait; } ;
struct TYPE_8__ {int tsens_power_up_force; int /*<<< orphan*/  tsens_clk_div; int /*<<< orphan*/  tsens_dac; } ;
struct TYPE_11__ {TYPE_1__ sar_tctrl2; TYPE_2__ sar_tctrl; } ;
struct TYPE_10__ {int /*<<< orphan*/  error_max; int /*<<< orphan*/  range_max; int /*<<< orphan*/  range_min; int /*<<< orphan*/  set_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_6__ SENS ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TSENS_XPD_WAIT_DEFAULT ; 
 TYPE_5__* dac_offset ; 

esp_err_t temp_sensor_set_config(temp_sensor_config_t tsens)
{
    SENS.sar_tctrl.tsens_dac = dac_offset[tsens.dac_offset].set_val;
    SENS.sar_tctrl.tsens_clk_div = tsens.clk_div;
    SENS.sar_tctrl.tsens_power_up_force = 1;
    SENS.sar_tctrl2.tsens_xpd_wait = TSENS_XPD_WAIT_DEFAULT;
    SENS.sar_tctrl2.tsens_xpd_force = 1;
    SENS.sar_tctrl2.tsens_reset = 1;// Reset the temp sensor.
    SENS.sar_tctrl2.tsens_reset = 0;// Clear the reset status.
    ESP_LOGI(TAG, "Config temperature range [%d°C ~ %d°C], error < %d°C",
             dac_offset[tsens.dac_offset].range_min, 
             dac_offset[tsens.dac_offset].range_max, 
             dac_offset[tsens.dac_offset].error_max);
    return ESP_OK;
}