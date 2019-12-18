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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  esp_bt_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BT_STATUS_ERR_ILLEGAL_PARAMETER_FMT ; 
 int /*<<< orphan*/  ESP_BT_STATUS_FAIL ; 
 int /*<<< orphan*/  ESP_BT_STATUS_PARAM_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ESP_BT_STATUS_PENDING ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BT_STATUS_TIMEOUT ; 
 int /*<<< orphan*/  ESP_BT_STATUS_UNACCEPT_CONN_INTERVAL ; 
#define  HCI_ERR_HOST_TIMEOUT 133 
#define  HCI_ERR_ILLEGAL_COMMAND 132 
#define  HCI_ERR_ILLEGAL_PARAMETER_FMT 131 
#define  HCI_ERR_PARAM_OUT_OF_RANGE 130 
#define  HCI_ERR_UNACCEPT_CONN_INTERVAL 129 
#define  HCI_SUCCESS 128 

esp_bt_status_t btc_hci_to_esp_status(uint8_t hci_status)
{
    esp_bt_status_t esp_status = ESP_BT_STATUS_FAIL;
    switch(hci_status) {
        case HCI_SUCCESS:
            esp_status = ESP_BT_STATUS_SUCCESS;
            break;
        case HCI_ERR_HOST_TIMEOUT:
            esp_status = ESP_BT_STATUS_TIMEOUT;
            break;
        case HCI_ERR_ILLEGAL_COMMAND:
            esp_status = ESP_BT_STATUS_PENDING;
            break;
        case HCI_ERR_UNACCEPT_CONN_INTERVAL:
            esp_status = ESP_BT_STATUS_UNACCEPT_CONN_INTERVAL;
            break;
        case HCI_ERR_PARAM_OUT_OF_RANGE:
            esp_status = ESP_BT_STATUS_PARAM_OUT_OF_RANGE;
            break;
        case HCI_ERR_ILLEGAL_PARAMETER_FMT:
            esp_status = ESP_BT_STATUS_ERR_ILLEGAL_PARAMETER_FMT;
            break;
        default:
            esp_status = ESP_BT_STATUS_FAIL;
            break;
    }

    return esp_status;
}