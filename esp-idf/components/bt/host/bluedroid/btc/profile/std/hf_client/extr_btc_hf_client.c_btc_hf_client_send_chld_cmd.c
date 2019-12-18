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
typedef  int esp_hf_chld_type_t ;
typedef  int /*<<< orphan*/  bt_status_t ;
struct TYPE_3__ {int chld_feat; int peer_feat; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {TYPE_1__ btc_hf_client_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_AT_CMD_CHLD ; 
 int BTA_HF_CLIENT_CHLD_MERGE ; 
 int BTA_HF_CLIENT_CHLD_MERGE_DETACH ; 
 int BTA_HF_CLIENT_CHLD_REL ; 
 int BTA_HF_CLIENT_PEER_ECC ; 
 int BTA_HF_CLIENT_PEER_FEAT_3WAY ; 
 int /*<<< orphan*/  BTA_HfClientSendAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  BT_STATUS_UNSUPPORTED ; 
 int /*<<< orphan*/  CHECK_HF_CLIENT_SLC_CONNECTED () ; 
#define  ESP_HF_CHLD_TYPE_HOLD_ACC 134 
#define  ESP_HF_CHLD_TYPE_MERGE 133 
#define  ESP_HF_CHLD_TYPE_MERGE_DETACH 132 
#define  ESP_HF_CHLD_TYPE_PRIV_X 131 
#define  ESP_HF_CHLD_TYPE_REL 130 
#define  ESP_HF_CHLD_TYPE_REL_ACC 129 
#define  ESP_HF_CHLD_TYPE_REL_X 128 
 TYPE_2__ hf_client_local_param ; 

__attribute__((used)) static bt_status_t btc_hf_client_send_chld_cmd(esp_hf_chld_type_t type, int idx)
{
    CHECK_HF_CLIENT_SLC_CONNECTED();

    switch (type)
    {
    case ESP_HF_CHLD_TYPE_REL:
        if (hf_client_local_param.btc_hf_client_cb.chld_feat & BTA_HF_CLIENT_CHLD_REL)
        {
            BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_CHLD, 0, 0, NULL);
            break;
        }
        return BT_STATUS_UNSUPPORTED;
    case ESP_HF_CHLD_TYPE_REL_ACC:
        // CHLD 1 is mandatory for 3 way calling
        if (hf_client_local_param.btc_hf_client_cb.peer_feat & BTA_HF_CLIENT_PEER_FEAT_3WAY)
        {
            BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_CHLD, 1, 0, NULL);
            break;
        }
        return BT_STATUS_UNSUPPORTED;
    case ESP_HF_CHLD_TYPE_HOLD_ACC:
        // CHLD 2 is mandatory for 3 way calling
        if (hf_client_local_param.btc_hf_client_cb.peer_feat & BTA_HF_CLIENT_PEER_FEAT_3WAY)
        {
            BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_CHLD, 2, 0, NULL);
            break;
        }
        return BT_STATUS_UNSUPPORTED;
    case ESP_HF_CHLD_TYPE_MERGE:
        if (hf_client_local_param.btc_hf_client_cb.chld_feat & BTA_HF_CLIENT_CHLD_MERGE)
        {
            BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_CHLD, 3, 0, NULL);
            break;
        }
        return BT_STATUS_UNSUPPORTED;
    case ESP_HF_CHLD_TYPE_MERGE_DETACH:
        if (hf_client_local_param.btc_hf_client_cb.chld_feat & BTA_HF_CLIENT_CHLD_MERGE_DETACH)
        {
            BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_CHLD, 4, 0, NULL);
            break;
        }
        return BT_STATUS_UNSUPPORTED;
    case ESP_HF_CHLD_TYPE_REL_X:
        if (hf_client_local_param.btc_hf_client_cb.peer_feat & BTA_HF_CLIENT_PEER_ECC)
        {
            if (idx < 1)
            {
                return BT_STATUS_FAIL;
            }
            BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_CHLD, 1, idx, NULL);
            break;
        }
        return BT_STATUS_UNSUPPORTED;
    case ESP_HF_CHLD_TYPE_PRIV_X:
        if (hf_client_local_param.btc_hf_client_cb.peer_feat & BTA_HF_CLIENT_PEER_ECC)
        {
            if (idx < 1)
            {
                return BT_STATUS_FAIL;
            }
            BTA_HfClientSendAT(hf_client_local_param.btc_hf_client_cb.handle, BTA_HF_CLIENT_AT_CMD_CHLD, 2, idx, NULL);
            break;
        }
        return BT_STATUS_UNSUPPORTED;

    }
    return BT_STATUS_SUCCESS;
}