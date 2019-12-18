#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int btc_init () ; 
 int osi_alarm_create_mux () ; 
 int /*<<< orphan*/  osi_alarm_init () ; 

esp_err_t bt_mesh_host_init(void)
{
    int rc;
    rc = btc_init();
    if (rc != 0) {
        return ESP_FAIL;
    }

    rc = osi_alarm_create_mux();
    if (rc != 0) {
        return ESP_FAIL;
    }

    osi_alarm_init();
    return ESP_OK;
}