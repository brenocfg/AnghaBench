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
#define  BTM_BUSY 136 
#define  BTM_CONTROL_LE_DATA_LEN_UNSUPPORTED 135 
#define  BTM_ERR_PROCESSING 134 
#define  BTM_ILLEGAL_VALUE 133 
#define  BTM_NO_RESOURCES 132 
#define  BTM_PEER_LE_DATA_LEN_UNSUPPORTED 131 
#define  BTM_SET_PRIVACY_FAIL 130 
#define  BTM_SET_PRIVACY_SUCCESS 129 
#define  BTM_SUCCESS 128 
 int /*<<< orphan*/  ESP_BT_STATUS_BUSY ; 
 int /*<<< orphan*/  ESP_BT_STATUS_CONTROL_LE_DATA_LEN_UNSUPPORTED ; 
 int /*<<< orphan*/  ESP_BT_STATUS_FAIL ; 
 int /*<<< orphan*/  ESP_BT_STATUS_NOMEM ; 
 int /*<<< orphan*/  ESP_BT_STATUS_PARM_INVALID ; 
 int /*<<< orphan*/  ESP_BT_STATUS_PEER_LE_DATA_LEN_UNSUPPORTED ; 
 int /*<<< orphan*/  ESP_BT_STATUS_PENDING ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 

esp_bt_status_t btc_btm_status_to_esp_status (uint8_t btm_status)
{
    esp_bt_status_t esp_status = ESP_BT_STATUS_FAIL;
    switch(btm_status){
        case BTM_SUCCESS:
            esp_status = ESP_BT_STATUS_SUCCESS;
            break;
        case BTM_BUSY:
            esp_status = ESP_BT_STATUS_BUSY;
            break;
        case BTM_NO_RESOURCES:
            esp_status = ESP_BT_STATUS_NOMEM;
            break;
        case BTM_ILLEGAL_VALUE:
            esp_status = ESP_BT_STATUS_PARM_INVALID;
            break;
        case BTM_ERR_PROCESSING:
            esp_status = ESP_BT_STATUS_PENDING;
            break;
        case BTM_PEER_LE_DATA_LEN_UNSUPPORTED:
            esp_status = ESP_BT_STATUS_PEER_LE_DATA_LEN_UNSUPPORTED;
            break;
        case BTM_CONTROL_LE_DATA_LEN_UNSUPPORTED:
            esp_status = ESP_BT_STATUS_CONTROL_LE_DATA_LEN_UNSUPPORTED;
            break;
        case BTM_SET_PRIVACY_SUCCESS:
            esp_status = ESP_BT_STATUS_SUCCESS;
            break;
        case BTM_SET_PRIVACY_FAIL:
            esp_status = ESP_BT_STATUS_FAIL;
            break;
        default:
            esp_status = ESP_BT_STATUS_FAIL;
            break;
    }

    return esp_status;
}