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
typedef  int /*<<< orphan*/  wps_factory_information_t ;
struct TYPE_3__ {int /*<<< orphan*/  device_name; int /*<<< orphan*/  model_number; int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer; } ;

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 TYPE_1__* os_zalloc (int) ; 
 TYPE_1__* s_factory_info ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int wps_set_default_factory(void)
{
    if (!s_factory_info) {
        s_factory_info = os_zalloc(sizeof(wps_factory_information_t));
        if (!s_factory_info) {
            wpa_printf(MSG_ERROR, "wps factory info malloc failed");
            return ESP_ERR_NO_MEM;
        }
    }

    sprintf(s_factory_info->manufacturer, "ESPRESSIF");
    sprintf(s_factory_info->model_name, "ESPRESSIF IOT");
    sprintf(s_factory_info->model_number, "ESP32");
    sprintf(s_factory_info->device_name, "ESP32 STATION");

    return ESP_OK;
}