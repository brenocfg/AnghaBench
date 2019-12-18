#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_66__   TYPE_9__ ;
typedef  struct TYPE_65__   TYPE_8__ ;
typedef  struct TYPE_64__   TYPE_7__ ;
typedef  struct TYPE_63__   TYPE_6__ ;
typedef  struct TYPE_62__   TYPE_5__ ;
typedef  struct TYPE_61__   TYPE_4__ ;
typedef  struct TYPE_60__   TYPE_3__ ;
typedef  struct TYPE_59__   TYPE_2__ ;
typedef  struct TYPE_58__   TYPE_28__ ;
typedef  struct TYPE_57__   TYPE_27__ ;
typedef  struct TYPE_56__   TYPE_26__ ;
typedef  struct TYPE_55__   TYPE_25__ ;
typedef  struct TYPE_54__   TYPE_24__ ;
typedef  struct TYPE_53__   TYPE_23__ ;
typedef  struct TYPE_52__   TYPE_22__ ;
typedef  struct TYPE_51__   TYPE_21__ ;
typedef  struct TYPE_50__   TYPE_20__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_19__ ;
typedef  struct TYPE_47__   TYPE_18__ ;
typedef  struct TYPE_46__   TYPE_17__ ;
typedef  struct TYPE_45__   TYPE_16__ ;
typedef  struct TYPE_44__   TYPE_15__ ;
typedef  struct TYPE_43__   TYPE_14__ ;
typedef  struct TYPE_42__   TYPE_13__ ;
typedef  struct TYPE_41__   TYPE_12__ ;
typedef  struct TYPE_40__   TYPE_11__ ;
typedef  struct TYPE_39__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_ATTR_VAL ;
struct TYPE_49__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_52__ {TYPE_1__ uu; int /*<<< orphan*/  len; } ;
typedef  TYPE_22__ tBT_UUID ;
typedef  int /*<<< orphan*/  tBTA_GATT_TRANSPORT ;
struct TYPE_61__ {int /*<<< orphan*/  inst_id; int /*<<< orphan*/  uuid; } ;
struct TYPE_53__ {int /*<<< orphan*/  is_primary; TYPE_4__ id; } ;
typedef  TYPE_23__ tBTA_GATT_SRVC_ID ;
typedef  int /*<<< orphan*/  tBTA_GATT_ATTR_VAL ;
struct TYPE_43__ {int /*<<< orphan*/  handle; } ;
struct TYPE_54__ {TYPE_14__ attr_value; } ;
typedef  TYPE_24__ tBTA_GATTS_RSP ;
typedef  int /*<<< orphan*/  tBTA_GATTS_ATTR_CONTROL ;
typedef  int /*<<< orphan*/  esp_gatt_rsp_t ;
struct TYPE_44__ {int /*<<< orphan*/  status; int /*<<< orphan*/  handle; } ;
struct TYPE_55__ {TYPE_15__ rsp; } ;
typedef  TYPE_25__ esp_ble_gatts_cb_param_t ;
struct TYPE_56__ {int act; scalar_t__ arg; } ;
typedef  TYPE_26__ btc_msg_t ;
struct TYPE_51__ {int /*<<< orphan*/  gatts_if; int /*<<< orphan*/  remote_bda; } ;
struct TYPE_50__ {int /*<<< orphan*/  conn_id; } ;
struct TYPE_48__ {int /*<<< orphan*/  is_direct; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  gatts_if; } ;
struct TYPE_46__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; int /*<<< orphan*/  handle; } ;
struct TYPE_45__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  status; int /*<<< orphan*/  trans_id; int /*<<< orphan*/ * rsp; } ;
struct TYPE_42__ {int /*<<< orphan*/  need_confirm; int /*<<< orphan*/  value; int /*<<< orphan*/  value_len; int /*<<< orphan*/  attr_handle; int /*<<< orphan*/  conn_id; } ;
struct TYPE_41__ {int /*<<< orphan*/  attr_control; int /*<<< orphan*/  descr_val; int /*<<< orphan*/  perm; int /*<<< orphan*/  service_handle; int /*<<< orphan*/  descr_uuid; } ;
struct TYPE_40__ {int /*<<< orphan*/  attr_control; int /*<<< orphan*/  char_val; int /*<<< orphan*/  property; int /*<<< orphan*/  perm; int /*<<< orphan*/  service_handle; int /*<<< orphan*/  char_uuid; } ;
struct TYPE_39__ {int /*<<< orphan*/  included_service_handle; int /*<<< orphan*/  service_handle; } ;
struct TYPE_66__ {int /*<<< orphan*/  service_handle; } ;
struct TYPE_65__ {int /*<<< orphan*/  service_handle; } ;
struct TYPE_64__ {int /*<<< orphan*/  service_handle; } ;
struct TYPE_63__ {int /*<<< orphan*/  srvc_inst_id; int /*<<< orphan*/  max_nb_attr; int /*<<< orphan*/  gatts_if; int /*<<< orphan*/  gatts_attr_db; } ;
struct TYPE_62__ {int /*<<< orphan*/  num_handle; int /*<<< orphan*/  gatts_if; int /*<<< orphan*/  service_id; } ;
struct TYPE_60__ {int /*<<< orphan*/  gatts_if; } ;
struct TYPE_59__ {int /*<<< orphan*/  app_id; } ;
struct TYPE_57__ {TYPE_21__ send_service_change; TYPE_20__ close; TYPE_19__ open; int /*<<< orphan*/  remote_bda; TYPE_17__ set_attr_val; TYPE_16__ send_rsp; TYPE_13__ send_ind; TYPE_12__ add_descr; TYPE_11__ add_char; TYPE_10__ add_incl_srvc; TYPE_9__ stop_srvc; TYPE_8__ start_srvc; TYPE_7__ delete_srvc; TYPE_6__ create_attr_tab; TYPE_5__ create_srvc; TYPE_3__ app_unreg; TYPE_2__ app_reg; } ;
typedef  TYPE_27__ btc_ble_gatts_args_t ;
struct TYPE_47__ {int /*<<< orphan*/  address; } ;
struct TYPE_58__ {TYPE_18__ bd_addr; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTA_DmAddBleDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_AddCharDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_22__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTA_GATTS_AddCharacteristic (int /*<<< orphan*/ ,TYPE_22__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTA_GATTS_AddIncludeService (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_AppDeregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_AppRegister (TYPE_22__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_CreateService (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_DeleteService (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_HandleValueIndication (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_Open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_SendRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_24__*) ; 
 int /*<<< orphan*/  BTA_GATTS_SendServiceChangeIndication (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_StartService (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_StopService (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATT_TRANSPORT_LE ; 
 int /*<<< orphan*/  BTA_SetAttributeValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  BTC_GATTS_ACT_ADD_CHAR 143 
#define  BTC_GATTS_ACT_ADD_CHAR_DESCR 142 
#define  BTC_GATTS_ACT_ADD_INCLUDE_SERVICE 141 
#define  BTC_GATTS_ACT_APP_REGISTER 140 
#define  BTC_GATTS_ACT_APP_UNREGISTER 139 
#define  BTC_GATTS_ACT_CLOSE 138 
#define  BTC_GATTS_ACT_CREATE_ATTR_TAB 137 
#define  BTC_GATTS_ACT_CREATE_SERVICE 136 
#define  BTC_GATTS_ACT_DELETE_SERVICE 135 
#define  BTC_GATTS_ACT_OPEN 134 
#define  BTC_GATTS_ACT_SEND_INDICATE 133 
#define  BTC_GATTS_ACT_SEND_RESPONSE 132 
#define  BTC_GATTS_ACT_SEND_SERVICE_CHANGE 131 
#define  BTC_GATTS_ACT_SET_ATTR_VALUE 130 
#define  BTC_GATTS_ACT_START_SERVICE 129 
#define  BTC_GATTS_ACT_STOP_SERVICE 128 
 int /*<<< orphan*/  BTC_GATT_GET_GATT_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_DEVICE_TYPE_BREDR ; 
 int /*<<< orphan*/  ESP_GATTS_RESPONSE_EVT ; 
 int /*<<< orphan*/  LEN_UUID_16 ; 
 int /*<<< orphan*/  _get_address_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_type ; 
 int /*<<< orphan*/  btc_gatts_act_create_attr_tab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_gatts_arg_deep_free (TYPE_26__*) ; 
 int /*<<< orphan*/  btc_gatts_cb_to_app (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_25__*) ; 
 int /*<<< orphan*/  btc_gatts_inter_cb ; 
 int /*<<< orphan*/  btc_to_bta_response (TYPE_24__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btc_to_bta_srvc_id (TYPE_23__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btc_to_bta_uuid (TYPE_22__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btif_get_device_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_type ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_28__* p_cb ; 

void btc_gatts_call_handler(btc_msg_t *msg)
{
    btc_ble_gatts_args_t *arg = (btc_ble_gatts_args_t *)msg->arg;

    switch (msg->act) {
    case BTC_GATTS_ACT_APP_REGISTER: {
        tBT_UUID uuid;

        uuid.len = LEN_UUID_16;
        uuid.uu.uuid16 = arg->app_reg.app_id;

        BTA_GATTS_AppRegister(&uuid, btc_gatts_inter_cb);

        break;
    }
    case BTC_GATTS_ACT_APP_UNREGISTER:
        BTA_GATTS_AppDeregister(arg->app_unreg.gatts_if);
        break;
    case BTC_GATTS_ACT_CREATE_SERVICE: {
        tBTA_GATT_SRVC_ID srvc_id;
        btc_to_bta_srvc_id(&srvc_id, &arg->create_srvc.service_id);
        BTA_GATTS_CreateService(arg->create_srvc.gatts_if, &srvc_id.id.uuid,
                                srvc_id.id.inst_id, arg->create_srvc.num_handle,
                                srvc_id.is_primary);
        break;
    }
   case BTC_GATTS_ACT_CREATE_ATTR_TAB:
    btc_gatts_act_create_attr_tab(arg->create_attr_tab.gatts_attr_db,
                                         arg->create_attr_tab.gatts_if,
                                         arg->create_attr_tab.max_nb_attr,
                                         arg->create_attr_tab.srvc_inst_id);
    break;
    case BTC_GATTS_ACT_DELETE_SERVICE:
        BTA_GATTS_DeleteService(arg->delete_srvc.service_handle);
        break;
    case BTC_GATTS_ACT_START_SERVICE:
        BTA_GATTS_StartService(arg->start_srvc.service_handle, BTA_GATT_TRANSPORT_LE);
        break;
    case BTC_GATTS_ACT_STOP_SERVICE:
        BTA_GATTS_StopService(arg->stop_srvc.service_handle);
        break;
    case BTC_GATTS_ACT_ADD_INCLUDE_SERVICE:
        BTA_GATTS_AddIncludeService(arg->add_incl_srvc.service_handle, arg->add_incl_srvc.included_service_handle);
        break;
    case BTC_GATTS_ACT_ADD_CHAR: {
        tBT_UUID uuid;
        btc_to_bta_uuid(&uuid, &arg->add_char.char_uuid);

        BTA_GATTS_AddCharacteristic(arg->add_char.service_handle, &uuid,
                                    arg->add_char.perm, arg->add_char.property,
                                    (tGATT_ATTR_VAL *)&arg->add_char.char_val,
                                    (tBTA_GATTS_ATTR_CONTROL *)&arg->add_char.attr_control);
        break;
    }
    case BTC_GATTS_ACT_ADD_CHAR_DESCR: {
        tBT_UUID uuid;
        btc_to_bta_uuid(&uuid, &arg->add_descr.descr_uuid);
        BTA_GATTS_AddCharDescriptor(arg->add_descr.service_handle, arg->add_descr.perm, &uuid,
                                   (tBTA_GATT_ATTR_VAL *)&arg->add_descr.descr_val,
                                   (tBTA_GATTS_ATTR_CONTROL *)&arg->add_descr.attr_control);
        break;
    }
    case BTC_GATTS_ACT_SEND_INDICATE:
        BTA_GATTS_HandleValueIndication(arg->send_ind.conn_id, arg->send_ind.attr_handle,
                                        arg->send_ind.value_len, arg->send_ind.value, arg->send_ind.need_confirm);
        break;
    case BTC_GATTS_ACT_SEND_RESPONSE: {
        esp_ble_gatts_cb_param_t param;
        esp_gatt_rsp_t *p_rsp = arg->send_rsp.rsp;

        if (p_rsp) {
            tBTA_GATTS_RSP rsp_struct;
            btc_to_bta_response(&rsp_struct, p_rsp);
            BTA_GATTS_SendRsp(arg->send_rsp.conn_id, arg->send_rsp.trans_id,
                              arg->send_rsp.status, &rsp_struct);
            param.rsp.handle = rsp_struct.attr_value.handle;
        } else {
            BTA_GATTS_SendRsp(arg->send_rsp.conn_id, arg->send_rsp.trans_id,
                              arg->send_rsp.status, NULL);
        }

        param.rsp.status = 0;
        btc_gatts_cb_to_app(ESP_GATTS_RESPONSE_EVT, BTC_GATT_GET_GATT_IF(arg->send_rsp.conn_id), &param);
        break;
    }
    case BTC_GATTS_ACT_SET_ATTR_VALUE:
        BTA_SetAttributeValue(arg->set_attr_val.handle, arg->set_attr_val.length,
                              arg->set_attr_val.value);
    break;
    case BTC_GATTS_ACT_OPEN: {
        // Ensure device is in inquiry database
        tBTA_GATT_TRANSPORT transport = BTA_GATT_TRANSPORT_LE;

        //TODO : implement address type and device type
#if  0
        if (_get_address_type(arg->remote_bda, &addr_type) &&
                btif_get_device_type(arg->remote_bda, &device_type) &&
                device_type != BT_DEVICE_TYPE_BREDR) {
            BTA_DmAddBleDevice(p_cb->bd_addr.address, addr_type, device_type);
        }
#else
        //BTA_DmAddBleDevice(p_cb->bd_addr.address, addr_type, device_type);
#endif
        /*
         not support background connection
        // Mark background connections
        if (!arg->open.is_direct) {
            BTA_DmBleSetBgConnType(BTM_BLE_CONN_AUTO, NULL);
        }
        */

        transport = BTA_GATT_TRANSPORT_LE;

        // Connect!
        BTA_GATTS_Open(arg->open.gatts_if, arg->open.remote_bda,
                       arg->open.is_direct, transport);
        break;
    }
    case BTC_GATTS_ACT_CLOSE:
        // TODO : implement cancel open
        // Cancel pending foreground/background connections
        //BTA_GATTS_CancelOpen(p_cb->server_if, p_cb->bd_addr.address, TRUE);
        //BTA_GATTS_CancelOpen(p_cb->server_if, p_cb->bd_addr.address, FALSE);

        // Close active connection
        if (arg->close.conn_id != 0) {
            BTA_GATTS_Close(arg->close.conn_id);
        }

        break;
    case BTC_GATTS_ACT_SEND_SERVICE_CHANGE: {
        BD_ADDR remote_bda;
        memcpy(remote_bda, arg->send_service_change.remote_bda, BD_ADDR_LEN);
        BTA_GATTS_SendServiceChangeIndication(arg->send_service_change.gatts_if, remote_bda);
        break;
    }
    default:
        break;
    }
    btc_gatts_arg_deep_free(msg);
}