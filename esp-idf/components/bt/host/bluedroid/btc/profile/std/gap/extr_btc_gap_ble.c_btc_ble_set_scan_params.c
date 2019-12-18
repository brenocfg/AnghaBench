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
typedef  int /*<<< orphan*/  tBLE_SCAN_PARAM_SETUP_CBACK ;
struct TYPE_3__ {scalar_t__ scan_type; int /*<<< orphan*/  scan_duplicate; int /*<<< orphan*/  own_addr_type; int /*<<< orphan*/  scan_filter_policy; int /*<<< orphan*/  scan_window; int /*<<< orphan*/  scan_interval; } ;
typedef  TYPE_1__ esp_ble_scan_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ADDR_TYPE_PUBLIC ; 
 scalar_t__ BLE_ADDR_TYPE_RPA_RANDOM ; 
 scalar_t__ BLE_ISVALID_PARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BLE_SCAN_DUPLICATE_DISABLE ; 
 scalar_t__ BLE_SCAN_DUPLICATE_MAX ; 
 int /*<<< orphan*/  BLE_SCAN_FILTER_ALLOW_ALL ; 
 scalar_t__ BLE_SCAN_FILTER_ALLOW_WLIST_PRA_DIR ; 
 int /*<<< orphan*/  BTA_DmSetBleScanFilterParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BTM_BLE_SCAN_INT_MAX ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_INT_MIN ; 
 scalar_t__ BTM_BLE_SCAN_MODE_ACTI ; 
 scalar_t__ BTM_BLE_SCAN_MODE_PASS ; 
 scalar_t__ BTM_BLE_SCAN_WIN_MAX ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_WIN_MIN ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  ESP_DEFAULT_GATT_IF ; 
 int /*<<< orphan*/  btc_scan_params_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_ble_set_scan_params(esp_ble_scan_params_t *scan_params, tBLE_SCAN_PARAM_SETUP_CBACK scan_param_setup_cback)
{
    if (BLE_ISVALID_PARAM(scan_params->scan_interval, BTM_BLE_SCAN_INT_MIN, BTM_BLE_SCAN_INT_MAX) &&
        BLE_ISVALID_PARAM(scan_params->scan_window, BTM_BLE_SCAN_WIN_MIN, BTM_BLE_SCAN_WIN_MAX) &&
        BLE_ISVALID_PARAM(scan_params->own_addr_type, BLE_ADDR_TYPE_PUBLIC, BLE_ADDR_TYPE_RPA_RANDOM) &&
        BLE_ISVALID_PARAM(scan_params->scan_filter_policy, BLE_SCAN_FILTER_ALLOW_ALL, BLE_SCAN_FILTER_ALLOW_WLIST_PRA_DIR) &&
        BLE_ISVALID_PARAM(scan_params->scan_duplicate, BLE_SCAN_DUPLICATE_DISABLE, BLE_SCAN_DUPLICATE_MAX -1) &&
        (scan_params->scan_type == BTM_BLE_SCAN_MODE_ACTI || scan_params->scan_type == BTM_BLE_SCAN_MODE_PASS)) {
        BTA_DmSetBleScanFilterParams(ESP_DEFAULT_GATT_IF,	/*client_if*/
                                     scan_params->scan_interval,
                                     scan_params->scan_window,
                                     scan_params->scan_type,
                                     scan_params->scan_filter_policy,
                                     scan_params->own_addr_type,
                                     scan_params->scan_duplicate,
                                     scan_param_setup_cback);
    } else {
        btc_scan_params_callback(ESP_DEFAULT_GATT_IF, BTM_ILLEGAL_VALUE);
    }
}