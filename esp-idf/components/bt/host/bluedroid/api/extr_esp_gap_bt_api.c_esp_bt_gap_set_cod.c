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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_bt_cod_t ;
typedef  int esp_bt_cod_mode_t ;
struct TYPE_7__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_6__ {int mode; int /*<<< orphan*/  cod; } ;
struct TYPE_8__ {TYPE_1__ set_cod; } ;
typedef  TYPE_3__ btc_gap_bt_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GAP_BT_ACT_SET_COD ; 
 int /*<<< orphan*/  BTC_PID_GAP_BT ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
#define  ESP_BT_CLR_COD_SERVICE_CLASS 132 
#define  ESP_BT_INIT_COD 131 
#define  ESP_BT_SET_COD_ALL 130 
#define  ESP_BT_SET_COD_MAJOR_MINOR 129 
#define  ESP_BT_SET_COD_SERVICE_CLASS 128 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_bluedroid_get_status () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

esp_err_t esp_bt_gap_set_cod(esp_bt_cod_t cod, esp_bt_cod_mode_t mode)
{
    btc_msg_t msg;
    btc_gap_bt_args_t arg;

    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }

    switch (mode) {
    case ESP_BT_SET_COD_MAJOR_MINOR:
    case ESP_BT_SET_COD_SERVICE_CLASS:
    case ESP_BT_CLR_COD_SERVICE_CLASS:
    case ESP_BT_SET_COD_ALL:
    case ESP_BT_INIT_COD:
        break;
    default:
        return ESP_ERR_INVALID_ARG;
        break;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GAP_BT;
    msg.act = BTC_GAP_BT_ACT_SET_COD;

    arg.set_cod.mode = mode;
    memcpy(&arg.set_cod.cod, &cod, sizeof(esp_bt_cod_t));
    return (btc_transfer_context(&msg, &arg, sizeof(btc_gap_bt_args_t), NULL) == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}