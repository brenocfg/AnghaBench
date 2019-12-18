#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int event; int len; TYPE_4__* p_data; } ;
typedef  TYPE_3__ tBTA_DM_SEARCH_PARAM ;
typedef  int tBTA_DM_SEARCH_EVT ;
struct TYPE_11__ {int /*<<< orphan*/  remt_name_not_required; int /*<<< orphan*/  p_eir; } ;
struct TYPE_10__ {int raw_data_size; int /*<<< orphan*/  p_raw_data; } ;
struct TYPE_13__ {TYPE_2__ inq_res; TYPE_1__ disc_res; } ;
typedef  TYPE_4__ tBTA_DM_SEARCH ;
struct TYPE_14__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_5__ btc_msg_t ;
typedef  int UINT16 ;

/* Variables and functions */
#define  BTA_DM_DISC_RES_EVT 129 
#define  BTA_DM_INQ_RES_EVT 128 
 int /*<<< orphan*/  BTC_GAP_BT_SEARCH_DEVICES_EVT ; 
 int /*<<< orphan*/  BTC_PID_GAP_BT ; 
 int /*<<< orphan*/  BTC_SIG_API_CB ; 
 int HCI_EXT_INQ_RESPONSE_LEN ; 
 int /*<<< orphan*/  btc_transfer_context (TYPE_5__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_eir_remote_name (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  search_devices_copy_cb ; 

__attribute__((used)) static void bte_search_devices_evt(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data)
{
    tBTA_DM_SEARCH_PARAM search;
    search.event = event;
    search.p_data = p_data;

    UINT16 param_len = 0;

    if (p_data) {
        param_len += sizeof(tBTA_DM_SEARCH);
    }
    /* Allocate buffer to hold the pointers (deep copy). The pointers will point to the end of the tBTA_DM_SEARCH */
    switch (event) {
    case BTA_DM_INQ_RES_EVT: {
        if (p_data->inq_res.p_eir) {
            param_len += HCI_EXT_INQ_RESPONSE_LEN;
        }
    }
    break;

    case BTA_DM_DISC_RES_EVT: {
        if (p_data->disc_res.raw_data_size && p_data->disc_res.p_raw_data) {
            param_len += p_data->disc_res.raw_data_size;
        }
    }
    break;
    }

    /* if remote name is available in EIR, set the flag so that stack doesn't trigger RNR */
    if (event == BTA_DM_INQ_RES_EVT) {
        p_data->inq_res.remt_name_not_required = check_eir_remote_name(p_data, NULL, NULL);
    }

    search.len = param_len;
    do {
        btc_msg_t msg;
        msg.sig = BTC_SIG_API_CB;
        msg.pid = BTC_PID_GAP_BT;
        msg.act = BTC_GAP_BT_SEARCH_DEVICES_EVT;

        btc_transfer_context(&msg, &search, sizeof(tBTA_DM_SEARCH_PARAM), search_devices_copy_cb);
    } while (0);
}