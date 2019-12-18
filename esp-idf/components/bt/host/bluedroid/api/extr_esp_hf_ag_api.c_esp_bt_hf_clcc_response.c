#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_hf_current_call_status_t ;
typedef  int /*<<< orphan*/  esp_hf_current_call_mpty_type_t ;
typedef  int /*<<< orphan*/  esp_hf_current_call_mode_t ;
typedef  int /*<<< orphan*/  esp_hf_current_call_direction_t ;
typedef  int /*<<< orphan*/  esp_hf_call_addr_type_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_bd_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_2__ btc_msg_t ;
struct TYPE_7__ {int index; char* number; int /*<<< orphan*/  type; int /*<<< orphan*/  mpty; int /*<<< orphan*/  mode; int /*<<< orphan*/  current_call_state; int /*<<< orphan*/  dir; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_9__ {TYPE_1__ clcc_rep; } ;
typedef  TYPE_3__ btc_hf_args_t ;
typedef  scalar_t__ bt_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_HF_CLCC_RESPONSE_EVT ; 
 int /*<<< orphan*/  BTC_PID_HF ; 
 int /*<<< orphan*/  BTC_SIG_API_CALL ; 
 scalar_t__ BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_hf_arg_deep_copy ; 
 scalar_t__ btc_transfer_context (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_bluedroid_get_status () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

esp_err_t esp_bt_hf_clcc_response(esp_bd_addr_t remote_addr, int index, esp_hf_current_call_direction_t dir,
                                 esp_hf_current_call_status_t current_call_state, esp_hf_current_call_mode_t mode,
                                 esp_hf_current_call_mpty_type_t mpty, char *number, esp_hf_call_addr_type_t type)
{
    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }
    btc_msg_t msg;
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_HF;
    msg.act = BTC_HF_CLCC_RESPONSE_EVT;

    btc_hf_args_t arg;
    memset(&arg, 0, sizeof(btc_hf_args_t));
    memcpy(&(arg.clcc_rep.remote_addr), remote_addr, sizeof(esp_bd_addr_t));
    //mandatory args
    arg.clcc_rep.index = index;
    arg.clcc_rep.dir = dir;
    arg.clcc_rep.current_call_state = current_call_state;
    arg.clcc_rep.mode = mode;
    arg.clcc_rep.mpty = mpty;
    // option args
    arg.clcc_rep.number = number; //deep_copy
    arg.clcc_rep.type = type;

    /* Switch to BTC context */
    bt_status_t stat = btc_transfer_context(&msg, &arg, sizeof(btc_hf_args_t), btc_hf_arg_deep_copy);
    return (stat == BT_STATUS_SUCCESS) ? ESP_OK : ESP_FAIL;
}