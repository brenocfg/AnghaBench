#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  esp_gatts_attr_db_t ;
typedef  int /*<<< orphan*/  esp_gatt_if_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_6__ {int /*<<< orphan*/ * gatts_attr_db; void* srvc_inst_id; void* max_nb_attr; int /*<<< orphan*/  gatts_if; } ;
struct TYPE_8__ {TYPE_1__ create_attr_tab; } ;
typedef  TYPE_3__ btc_ble_gatts_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GATTS_ACT_CREATE_ATTR_TAB ; 
 int /*<<< orphan*/  BTC_PID_GATTS ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_gatts_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

esp_err_t esp_ble_gatts_create_attr_tab(const esp_gatts_attr_db_t *gatts_attr_db,
                                        esp_gatt_if_t gatts_if,
                                        uint8_t max_nb_attr,
                                        uint8_t srvc_inst_id)
{
    btc_msg_t msg;
    btc_ble_gatts_args_t arg;

    ESP_BLUEDROID_STATUS_CHECK(ESP_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTS;
    msg.act = BTC_GATTS_ACT_CREATE_ATTR_TAB;
    arg.create_attr_tab.gatts_if = gatts_if;
    arg.create_attr_tab.max_nb_attr = max_nb_attr;
    arg.create_attr_tab.srvc_inst_id = srvc_inst_id;
    arg.create_attr_tab.gatts_attr_db = (esp_gatts_attr_db_t *)gatts_attr_db;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gatts_args_t), btc_gatts_arg_deep_copy)
            == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}