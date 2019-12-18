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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ esp_bt_inq_mode_t ;
struct TYPE_7__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_6__ {scalar_t__ num_rsps; scalar_t__ inq_len; scalar_t__ mode; } ;
struct TYPE_8__ {TYPE_1__ start_disc; } ;
typedef  TYPE_3__ btc_gap_bt_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GAP_BT_ACT_START_DISCOVERY ; 
 int /*<<< orphan*/  BTC_PID_GAP_BT ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 scalar_t__ ESP_BT_GAP_MAX_INQ_LEN ; 
 scalar_t__ ESP_BT_GAP_MIN_INQ_LEN ; 
 scalar_t__ ESP_BT_INQ_MODE_GENERAL_INQUIRY ; 
 scalar_t__ ESP_BT_INQ_MODE_LIMITED_INQUIRY ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_bluedroid_get_status () ; 

esp_err_t esp_bt_gap_start_discovery(esp_bt_inq_mode_t mode, uint8_t inq_len, uint8_t num_rsps)
{
    btc_msg_t msg;
    btc_gap_bt_args_t arg;

    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }

    if (mode != ESP_BT_INQ_MODE_GENERAL_INQUIRY &&
            mode != ESP_BT_INQ_MODE_LIMITED_INQUIRY) {
        return ESP_ERR_INVALID_ARG;
    }

    if (inq_len < ESP_BT_GAP_MIN_INQ_LEN ||
            inq_len > ESP_BT_GAP_MAX_INQ_LEN) {
        return ESP_ERR_INVALID_ARG;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GAP_BT;
    msg.act = BTC_GAP_BT_ACT_START_DISCOVERY;

    arg.start_disc.mode = mode;
    arg.start_disc.inq_len = inq_len;
    arg.start_disc.num_rsps = num_rsps;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_gap_bt_args_t), NULL) == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}