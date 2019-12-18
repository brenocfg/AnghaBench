#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int act; scalar_t__ arg; } ;
typedef  TYPE_4__ btc_msg_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_url; int /*<<< orphan*/  p_manufacturer_data; } ;
struct TYPE_8__ {TYPE_3__ eir_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
struct TYPE_12__ {TYPE_1__ config_eir; TYPE_2__ set_security_param; } ;
typedef  TYPE_5__ btc_gap_bt_args_t ;

/* Variables and functions */
#define  BTC_GAP_BT_ACT_CANCEL_DISCOVERY 143 
#define  BTC_GAP_BT_ACT_CONFIG_EIR 142 
#define  BTC_GAP_BT_ACT_CONFIRM_REPLY 141 
#define  BTC_GAP_BT_ACT_GET_REMOTE_SERVICES 140 
#define  BTC_GAP_BT_ACT_GET_REMOTE_SERVICE_RECORD 139 
#define  BTC_GAP_BT_ACT_PASSKEY_REPLY 138 
#define  BTC_GAP_BT_ACT_PIN_REPLY 137 
#define  BTC_GAP_BT_ACT_READ_REMOTE_NAME 136 
#define  BTC_GAP_BT_ACT_READ_RSSI_DELTA 135 
#define  BTC_GAP_BT_ACT_REMOVE_BOND_DEVICE 134 
#define  BTC_GAP_BT_ACT_SET_AFH_CHANNELS 133 
#define  BTC_GAP_BT_ACT_SET_COD 132 
#define  BTC_GAP_BT_ACT_SET_PIN_TYPE 131 
#define  BTC_GAP_BT_ACT_SET_SCAN_MODE 130 
#define  BTC_GAP_BT_ACT_SET_SECURITY_PARAM 129 
#define  BTC_GAP_BT_ACT_START_DISCOVERY 128 
 int /*<<< orphan*/  BTC_TRACE_ERROR (char*,int,TYPE_5__*) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

void btc_gap_bt_arg_deep_free(btc_msg_t *msg)
{
    btc_gap_bt_args_t *arg = (btc_gap_bt_args_t *)msg->arg;
    switch (msg->act) {
    case BTC_GAP_BT_ACT_SET_SCAN_MODE:
    case BTC_GAP_BT_ACT_START_DISCOVERY:
    case BTC_GAP_BT_ACT_CANCEL_DISCOVERY:
    case BTC_GAP_BT_ACT_GET_REMOTE_SERVICES:
    case BTC_GAP_BT_ACT_GET_REMOTE_SERVICE_RECORD:
    case BTC_GAP_BT_ACT_SET_COD:
    case BTC_GAP_BT_ACT_READ_RSSI_DELTA:
    case BTC_GAP_BT_ACT_REMOVE_BOND_DEVICE:
    case BTC_GAP_BT_ACT_PIN_REPLY:
    case BTC_GAP_BT_ACT_SET_PIN_TYPE:
    case BTC_GAP_BT_ACT_SET_AFH_CHANNELS:
    case BTC_GAP_BT_ACT_READ_REMOTE_NAME:
        break;
#if (BT_SSP_INCLUDED == TRUE)
    case BTC_GAP_BT_ACT_PASSKEY_REPLY:
    case BTC_GAP_BT_ACT_CONFIRM_REPLY:
        break;
    case BTC_GAP_BT_ACT_SET_SECURITY_PARAM:
        if (arg->set_security_param.value) {
            osi_free(arg->set_security_param.value);
        }
        break;
#endif ///BT_SSP_INCLUDED == TRUE

    case BTC_GAP_BT_ACT_CONFIG_EIR:
        if (arg->config_eir.eir_data.p_manufacturer_data) {
            osi_free(arg->config_eir.eir_data.p_manufacturer_data);
        }
        if (arg->config_eir.eir_data.p_url) {
            osi_free(arg->config_eir.eir_data.p_url);
        }
        break;
    default:
        BTC_TRACE_ERROR("Unhandled deep copy %d, arg: %p\n", msg->act, arg);
        break;
    }
}