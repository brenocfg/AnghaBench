#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int len; TYPE_3__* p_data; scalar_t__ event; } ;
typedef  TYPE_2__ tBTA_DM_SEARCH_PARAM ;
typedef  scalar_t__ tBTA_DM_SEARCH_EVT ;
struct TYPE_8__ {scalar_t__ raw_data_size; scalar_t__ p_raw_data; } ;
struct TYPE_10__ {TYPE_1__ disc_res; } ;
typedef  TYPE_3__ tBTA_DM_SEARCH ;
struct TYPE_11__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_4__ btc_msg_t ;
typedef  int UINT16 ;

/* Variables and functions */
 scalar_t__ BTA_DM_DISC_RES_EVT ; 
 int /*<<< orphan*/  BTC_GAP_BT_SEARCH_SERVICE_RECORD_EVT ; 
 int /*<<< orphan*/  BTC_PID_GAP_BT ; 
 int /*<<< orphan*/  BTC_SIG_API_CB ; 
 int /*<<< orphan*/  btc_transfer_context (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_service_record_copy_cb ; 

__attribute__((used)) static void bte_dm_remote_service_record_evt(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data)
{
    tBTA_DM_SEARCH_PARAM search;
    search.event = event;
    search.p_data = p_data;
    UINT16 param_len = 0;

    if (p_data) {
        param_len += sizeof(tBTA_DM_SEARCH);
    }
    /* Allocate buffer to hold the pointers (deep copy). The pointers will point to the end of the tBTA_DM_SEARCH */
    if (event == BTA_DM_DISC_RES_EVT) {
        if (p_data->disc_res.raw_data_size && p_data->disc_res.p_raw_data) {
            param_len += p_data->disc_res.raw_data_size;
        }
    }
    search.len = param_len;
    do {
        btc_msg_t msg;
        msg.sig = BTC_SIG_API_CB;
        msg.pid = BTC_PID_GAP_BT;
        msg.act = BTC_GAP_BT_SEARCH_SERVICE_RECORD_EVT;
        btc_transfer_context(&msg, &search, sizeof(tBTA_DM_SEARCH_PARAM), search_service_record_copy_cb);
    } while (0);

}