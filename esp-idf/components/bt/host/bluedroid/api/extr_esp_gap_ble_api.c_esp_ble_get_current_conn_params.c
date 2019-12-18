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
struct TYPE_3__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  interval; } ;
typedef  TYPE_1__ esp_gap_conn_params_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_bd_addr_t ;

/* Variables and functions */
 scalar_t__ BTM_GetCurrentConnParams (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 

esp_err_t esp_ble_get_current_conn_params(esp_bd_addr_t bd_addr, esp_gap_conn_params_t *conn_params)
{
    if(!bd_addr || !conn_params) {
        return ESP_ERR_INVALID_ARG;
    }
    if(BTM_GetCurrentConnParams(bd_addr, &conn_params->interval, &conn_params->latency, &conn_params->timeout)) {
        return ESP_OK;
    }
    return ESP_ERR_NOT_FOUND;
}