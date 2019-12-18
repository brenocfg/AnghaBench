#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int event; TYPE_4__* p_data; } ;
typedef  TYPE_5__ tBTA_DM_SEARCH_PARAM ;
struct TYPE_8__ {int /*<<< orphan*/  stat; } ;
struct TYPE_9__ {int /*<<< orphan*/  bda; } ;
struct TYPE_13__ {TYPE_1__ rmt_srvc_rec; TYPE_2__ rmt_srvcs; } ;
typedef  TYPE_6__ esp_bt_gap_cb_param_t ;
struct TYPE_10__ {int /*<<< orphan*/  raw_data_size; int /*<<< orphan*/  p_raw_data; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_11__ {TYPE_3__ disc_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
#define  BTA_DM_DISC_CMPL_EVT 129 
#define  BTA_DM_DISC_RES_EVT 128 
 int /*<<< orphan*/  ESP_BT_GAP_RMT_SRVC_REC_EVT ; 
 int /*<<< orphan*/  ESP_BT_STATUS_FAIL ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  btc_gap_bt_cb_to_app (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_gap_bt_search_service_record(char *p_param)
{
    tBTA_DM_SEARCH_PARAM *p_data = (tBTA_DM_SEARCH_PARAM *)p_param;

    switch (p_data->event) {
    case BTA_DM_DISC_RES_EVT: {
        esp_bt_gap_cb_param_t param;
        memcpy(param.rmt_srvcs.bda, p_data->p_data->disc_res.bd_addr, BD_ADDR_LEN);
        if (p_data->p_data->disc_res.p_raw_data && p_data->p_data->disc_res.raw_data_size > 0) {
            param.rmt_srvc_rec.stat = ESP_BT_STATUS_SUCCESS;
            // param.rmt_srvc_rec.raw_data_size = p_data->p_data->disc_res.raw_data_size;
            // param.rmt_srvc_rec.raw_data = p_data->p_data->disc_res.p_raw_data;
        } else {
            param.rmt_srvc_rec.stat = ESP_BT_STATUS_FAIL;
            // param.rmt_srvc_rec.raw_data_size = 0;
            // param.rmt_srvc_rec.raw_data = NULL;
        }
        btc_gap_bt_cb_to_app(ESP_BT_GAP_RMT_SRVC_REC_EVT, &param);
    }
    break;
    case BTA_DM_DISC_CMPL_EVT:
    default:
        break;
    }
}