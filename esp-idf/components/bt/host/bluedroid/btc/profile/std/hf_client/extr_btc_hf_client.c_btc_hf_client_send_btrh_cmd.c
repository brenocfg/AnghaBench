#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int esp_hf_btrh_cmd_t ;
typedef  int /*<<< orphan*/  bt_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {TYPE_1__ btc_hf_client_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_AT_CMD_BTRH ; 
 int /*<<< orphan*/  BTA_HfClientSendAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  CHECK_HF_CLIENT_SLC_CONNECTED () ; 
#define  ESP_HF_BTRH_CMD_ACCEPT 130 
#define  ESP_HF_BTRH_CMD_HOLD 129 
#define  ESP_HF_BTRH_CMD_REJECT 128 
 TYPE_2__ hf_client_local_param ; 

__attribute__((used)) static bt_status_t btc_hf_client_send_btrh_cmd(esp_hf_btrh_cmd_t btrh)
{
    CHECK_HF_CLIENT_SLC_CONNECTED();

    switch (btrh) {
    case ESP_HF_BTRH_CMD_HOLD:
        BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_BTRH, 0, 0, NULL);
        break;
    case ESP_HF_BTRH_CMD_ACCEPT:
        BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_BTRH, 1, 0, NULL);
        break;
    case ESP_HF_BTRH_CMD_REJECT:
        BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_BTRH, 2, 0, NULL);
        break;
    default:
        return BT_STATUS_FAIL;
    }

    return BT_STATUS_SUCCESS;
}