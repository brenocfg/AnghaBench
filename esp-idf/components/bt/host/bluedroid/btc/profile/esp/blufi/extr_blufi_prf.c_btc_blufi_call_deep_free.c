#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {struct TYPE_14__* softap_passwd; struct TYPE_14__* softap_ssid; struct TYPE_14__* sta_passwd; struct TYPE_14__* sta_ssid; } ;
typedef  TYPE_4__ uint8_t ;
typedef  TYPE_4__ esp_blufi_extra_info_t ;
typedef  TYPE_4__ esp_blufi_ap_record_t ;
struct TYPE_15__ {int act; scalar_t__ arg; } ;
typedef  TYPE_7__ btc_msg_t ;
struct TYPE_13__ {TYPE_4__* data; } ;
struct TYPE_12__ {scalar_t__ list; } ;
struct TYPE_11__ {scalar_t__ extra_info; } ;
struct TYPE_16__ {TYPE_3__ custom_data; TYPE_2__ wifi_list; TYPE_1__ wifi_conn_report; } ;
typedef  TYPE_8__ btc_blufi_args_t ;

/* Variables and functions */
#define  BTC_BLUFI_ACT_SEND_CFG_REPORT 130 
#define  BTC_BLUFI_ACT_SEND_CUSTOM_DATA 129 
#define  BTC_BLUFI_ACT_SEND_WIFI_LIST 128 
 int /*<<< orphan*/  osi_free (TYPE_4__*) ; 

void btc_blufi_call_deep_free(btc_msg_t *msg)
{
    btc_blufi_args_t *arg = (btc_blufi_args_t *)msg->arg;

    switch (msg->act) {
    case BTC_BLUFI_ACT_SEND_CFG_REPORT: {
        esp_blufi_extra_info_t *info = (esp_blufi_extra_info_t *)arg->wifi_conn_report.extra_info;

        if (info == NULL) {
            return;
        }
        if (info->sta_ssid) {
            osi_free(info->sta_ssid);
        }
        if (info->sta_passwd) {
            osi_free(info->sta_passwd);
        }
        if (info->softap_ssid) {
            osi_free(info->softap_ssid);
        }
        if (info->softap_passwd) {
            osi_free(info->softap_passwd);
        }
        osi_free(info);
        break;
    }
    case BTC_BLUFI_ACT_SEND_WIFI_LIST:{
        esp_blufi_ap_record_t *list = (esp_blufi_ap_record_t *)arg->wifi_list.list;
        if (list){
            osi_free(list);
        }
        break;
    }
    case BTC_BLUFI_ACT_SEND_CUSTOM_DATA:{
        uint8_t *data = arg->custom_data.data;
        if(data) {
            osi_free(data);
        }
        break;
    }
    default:
        break;
    }
}