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
#define  BTA_BUSY 134 
#define  BTA_EIR_TOO_LARGE 133 
#define  BTA_FAILURE 132 
#define  BTA_NO_RESOURCES 131 
#define  BTA_PENDING 130 
#define  BTA_SUCCESS 129 
#define  BTA_WRONG_MODE 128 
 int /*<<< orphan*/  ESP_BT_STATUS_BUSY ; 
 int /*<<< orphan*/  ESP_BT_STATUS_EIR_TOO_LARGE ; 
 int /*<<< orphan*/  ESP_BT_STATUS_FAIL ; 
 int /*<<< orphan*/  ESP_BT_STATUS_NOMEM ; 
 int /*<<< orphan*/  ESP_BT_STATUS_NOT_READY ; 
 int /*<<< orphan*/  ESP_BT_STATUS_PENDING ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 

esp_bt_status_t btc_bta_status_to_esp_status (uint8_t bta_status)
{
    esp_bt_status_t esp_status = ESP_BT_STATUS_FAIL;
    switch(bta_status){
        case BTA_SUCCESS:
            esp_status = ESP_BT_STATUS_SUCCESS;
            break;
        case BTA_FAILURE:
            esp_status = ESP_BT_STATUS_FAIL;
            break;
        case BTA_PENDING:
            esp_status = ESP_BT_STATUS_PENDING;
            break;
        case BTA_BUSY:
            esp_status = ESP_BT_STATUS_BUSY;
            break;
        case BTA_NO_RESOURCES:
            esp_status = ESP_BT_STATUS_NOMEM;
            break;
        case BTA_WRONG_MODE:
            esp_status = ESP_BT_STATUS_NOT_READY;
            break;
        case BTA_EIR_TOO_LARGE:
            esp_status = ESP_BT_STATUS_EIR_TOO_LARGE;
            break;
        default:
            esp_status = ESP_BT_STATUS_FAIL;
            break;
    }

    return esp_status;
}