#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_27__ ;
typedef  struct TYPE_40__   TYPE_26__ ;
typedef  struct TYPE_39__   TYPE_25__ ;
typedef  struct TYPE_38__   TYPE_20__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_18__ ;
typedef  struct TYPE_35__   TYPE_17__ ;
typedef  struct TYPE_34__   TYPE_16__ ;
typedef  struct TYPE_33__   TYPE_15__ ;
typedef  struct TYPE_32__   TYPE_14__ ;
typedef  struct TYPE_31__   TYPE_13__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  notify_data ;
typedef  int /*<<< orphan*/  indicate_data ;
typedef  int esp_gatts_cb_event_t ;
struct TYPE_32__ {int len; int* value; int /*<<< orphan*/  handle; } ;
struct TYPE_35__ {TYPE_14__ attr_value; } ;
typedef  TYPE_17__ esp_gatt_rsp_t ;
typedef  int /*<<< orphan*/  esp_gatt_if_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_49__ {int status; int* value; int len; } ;
struct TYPE_48__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/ * remote_bda; } ;
struct TYPE_47__ {int /*<<< orphan*/  service_handle; int /*<<< orphan*/  status; } ;
struct TYPE_46__ {int /*<<< orphan*/  service_handle; int /*<<< orphan*/  attr_handle; int /*<<< orphan*/  status; } ;
struct TYPE_44__ {int /*<<< orphan*/  attr_handle; int /*<<< orphan*/  service_handle; int /*<<< orphan*/  status; } ;
struct TYPE_42__ {int /*<<< orphan*/  service_handle; int /*<<< orphan*/  status; } ;
struct TYPE_37__ {int mtu; } ;
struct TYPE_34__ {int len; int* value; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  handle; int /*<<< orphan*/  is_prep; } ;
struct TYPE_33__ {int /*<<< orphan*/  trans_id; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  handle; } ;
struct TYPE_28__ {int /*<<< orphan*/  app_id; int /*<<< orphan*/  status; } ;
struct TYPE_36__ {TYPE_9__ conf; TYPE_8__ connect; TYPE_7__ start; TYPE_6__ add_char_descr; TYPE_4__ add_char; TYPE_2__ create; TYPE_1__ mtu; TYPE_16__ write; TYPE_15__ read; TYPE_10__ reg; } ;
typedef  TYPE_18__ esp_ble_gatts_cb_param_t ;
struct TYPE_45__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_43__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_41__ {TYPE_3__ uuid; void* len; } ;
struct TYPE_40__ {TYPE_5__ uuid; void* len; } ;
struct TYPE_29__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_30__ {TYPE_11__ uuid; void* len; } ;
struct TYPE_31__ {int inst_id; TYPE_12__ uuid; } ;
struct TYPE_39__ {int is_primary; TYPE_13__ id; } ;
struct TYPE_38__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  descr_handle; TYPE_26__ descr_uuid; int /*<<< orphan*/  service_handle; int /*<<< orphan*/  char_handle; TYPE_27__ char_uuid; TYPE_25__ service_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_BLE_COEX_TAG ; 
#define  ESP_GATTS_ADD_CHAR_DESCR_EVT 148 
#define  ESP_GATTS_ADD_CHAR_EVT 147 
#define  ESP_GATTS_ADD_INCL_SRVC_EVT 146 
#define  ESP_GATTS_CANCEL_OPEN_EVT 145 
#define  ESP_GATTS_CLOSE_EVT 144 
#define  ESP_GATTS_CONF_EVT 143 
#define  ESP_GATTS_CONGEST_EVT 142 
#define  ESP_GATTS_CONNECT_EVT 141 
#define  ESP_GATTS_CREATE_EVT 140 
#define  ESP_GATTS_DELETE_EVT 139 
#define  ESP_GATTS_DISCONNECT_EVT 138 
#define  ESP_GATTS_EXEC_WRITE_EVT 137 
#define  ESP_GATTS_LISTEN_EVT 136 
#define  ESP_GATTS_MTU_EVT 135 
#define  ESP_GATTS_OPEN_EVT 134 
#define  ESP_GATTS_READ_EVT 133 
#define  ESP_GATTS_REG_EVT 132 
#define  ESP_GATTS_START_EVT 131 
#define  ESP_GATTS_STOP_EVT 130 
#define  ESP_GATTS_UNREG_EVT 129 
#define  ESP_GATTS_WRITE_EVT 128 
 int ESP_GATT_CHAR_PROP_BIT_INDICATE ; 
 int ESP_GATT_CHAR_PROP_BIT_NOTIFY ; 
 int ESP_GATT_CHAR_PROP_BIT_READ ; 
 int ESP_GATT_CHAR_PROP_BIT_WRITE ; 
 int ESP_GATT_OK ; 
 int ESP_GATT_PERM_READ ; 
 int ESP_GATT_PERM_WRITE ; 
 int /*<<< orphan*/  ESP_GATT_UUID_CHAR_CLIENT_CONFIG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 void* ESP_UUID_LEN_16 ; 
 int /*<<< orphan*/  GATTS_CHAR_UUID_B ; 
 int /*<<< orphan*/  GATTS_NUM_HANDLE_B ; 
 int /*<<< orphan*/  GATTS_SERVICE_UUID_B ; 
 size_t PROFILE_B_APP_ID ; 
 int /*<<< orphan*/  b_prepare_write_env ; 
 int b_property ; 
 int /*<<< orphan*/  esp_ble_gatts_add_char (int /*<<< orphan*/ ,TYPE_27__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_gatts_add_char_descr (int /*<<< orphan*/ ,TYPE_26__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_gatts_create_service (int /*<<< orphan*/ ,TYPE_25__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_gatts_send_indicate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  esp_ble_gatts_send_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_17__*) ; 
 int /*<<< orphan*/  esp_ble_gatts_start_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  example_exec_write_event_env (int /*<<< orphan*/ *,TYPE_18__*) ; 
 int /*<<< orphan*/  example_write_event_env (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_18__*) ; 
 TYPE_20__* gl_profile_tab ; 
 int /*<<< orphan*/  memset (TYPE_17__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gatts_profile_b_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
    case ESP_GATTS_REG_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
        gl_profile_tab[PROFILE_B_APP_ID].service_id.is_primary = true;
        gl_profile_tab[PROFILE_B_APP_ID].service_id.id.inst_id = 0x00;
        gl_profile_tab[PROFILE_B_APP_ID].service_id.id.uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_B_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_B;

        esp_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_B_APP_ID].service_id, GATTS_NUM_HANDLE_B);
        break;
    case ESP_GATTS_READ_EVT: {
        ESP_LOGI(BT_BLE_COEX_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
        esp_gatt_rsp_t rsp;
        memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
        rsp.attr_value.handle = param->read.handle;
        rsp.attr_value.len = 4;
        rsp.attr_value.value[0] = 0xde;
        rsp.attr_value.value[1] = 0xed;
        rsp.attr_value.value[2] = 0xbe;
        rsp.attr_value.value[3] = 0xef;
        esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id,
                                    ESP_GATT_OK, &rsp);
        break;
    }
    case ESP_GATTS_WRITE_EVT: {
        ESP_LOGI(BT_BLE_COEX_TAG, "GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d\n", param->write.conn_id, param->write.trans_id, param->write.handle);
        if (!param->write.is_prep){
            ESP_LOGI(BT_BLE_COEX_TAG, "GATT_WRITE_EVT, value len %d, value :", param->write.len);
            esp_log_buffer_hex(BT_BLE_COEX_TAG, param->write.value, param->write.len);
            if (gl_profile_tab[PROFILE_B_APP_ID].descr_handle == param->write.handle && param->write.len == 2){
                uint16_t descr_value= param->write.value[1]<<8 | param->write.value[0];
                if (descr_value == 0x0001){
                    if (b_property & ESP_GATT_CHAR_PROP_BIT_NOTIFY){
                        ESP_LOGI(BT_BLE_COEX_TAG, "notify enable");
                        uint8_t notify_data[15];
                        for (int i = 0; i < sizeof(notify_data); ++i)
                        {
                            notify_data[i] = i%0xff;
                        }
                        //the size of notify_data[] need less than MTU size
                        esp_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_B_APP_ID].char_handle,
                                                sizeof(notify_data), notify_data, false);
                    }
                }else if (descr_value == 0x0002){
                    if (b_property & ESP_GATT_CHAR_PROP_BIT_INDICATE){
                        ESP_LOGI(BT_BLE_COEX_TAG, "indicate enable");
                        uint8_t indicate_data[15];
                        for (int i = 0; i < sizeof(indicate_data); ++i)
                        {
                            indicate_data[i] = i%0xff;
                        }
                        //the size of indicate_data[] need less than MTU size
                        esp_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_B_APP_ID].char_handle,
                                                sizeof(indicate_data), indicate_data, true);
                    }
                }
                else if (descr_value == 0x0000){
                    ESP_LOGI(BT_BLE_COEX_TAG, "notify/indicate disable ");
                }else{
                    ESP_LOGE(BT_BLE_COEX_TAG, "unknown value");
                }

            }
        }
        example_write_event_env(gatts_if, &b_prepare_write_env, param);
        break;
    }
    case ESP_GATTS_EXEC_WRITE_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG,"ESP_GATTS_EXEC_WRITE_EVT");
        esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
        example_exec_write_event_env(&b_prepare_write_env, param);
        break;
    case ESP_GATTS_MTU_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
        break;
    case ESP_GATTS_UNREG_EVT:
        break;
    case ESP_GATTS_CREATE_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
        gl_profile_tab[PROFILE_B_APP_ID].service_handle = param->create.service_handle;
        gl_profile_tab[PROFILE_B_APP_ID].char_uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_B_APP_ID].char_uuid.uuid.uuid16 = GATTS_CHAR_UUID_B;

        esp_ble_gatts_start_service(gl_profile_tab[PROFILE_B_APP_ID].service_handle);
        b_property = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
        esp_err_t add_char_ret =esp_ble_gatts_add_char( gl_profile_tab[PROFILE_B_APP_ID].service_handle, &gl_profile_tab[PROFILE_B_APP_ID].char_uuid,
                                                        ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                                                        b_property,
                                                        NULL, NULL);
        if (add_char_ret){
            ESP_LOGE(BT_BLE_COEX_TAG, "add char failed, error code = 0x%x",add_char_ret);
        }
        break;
    case ESP_GATTS_ADD_INCL_SRVC_EVT:
        break;
    case ESP_GATTS_ADD_CHAR_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "ADD_CHAR_EVT, status %d,  attr_handle %d, service_handle %d\n",
                 param->add_char.status, param->add_char.attr_handle, param->add_char.service_handle);

        gl_profile_tab[PROFILE_B_APP_ID].char_handle = param->add_char.attr_handle;
        gl_profile_tab[PROFILE_B_APP_ID].descr_uuid.len = ESP_UUID_LEN_16;
        gl_profile_tab[PROFILE_B_APP_ID].descr_uuid.uuid.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
        esp_ble_gatts_add_char_descr(gl_profile_tab[PROFILE_B_APP_ID].service_handle, &gl_profile_tab[PROFILE_B_APP_ID].descr_uuid,
                                     ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                                     NULL, NULL);
        break;
    case ESP_GATTS_ADD_CHAR_DESCR_EVT:
        gl_profile_tab[PROFILE_B_APP_ID].descr_handle = param->add_char_descr.attr_handle;
        ESP_LOGI(BT_BLE_COEX_TAG, "ADD_DESCR_EVT, status %d, attr_handle %d, service_handle %d\n",
                 param->add_char_descr.status, param->add_char_descr.attr_handle, param->add_char_descr.service_handle);
        break;
    case ESP_GATTS_DELETE_EVT:
        break;
    case ESP_GATTS_START_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n",
                 param->start.status, param->start.service_handle);
        break;
    case ESP_GATTS_STOP_EVT:
        break;
    case ESP_GATTS_CONNECT_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:",
                 param->connect.conn_id,
                 param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                 param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
        gl_profile_tab[PROFILE_B_APP_ID].conn_id = param->connect.conn_id;
        break;
    case ESP_GATTS_CONF_EVT:
        ESP_LOGI(BT_BLE_COEX_TAG, "ESP_GATTS_CONF_EVT status %d", param->conf.status);
        if (param->conf.status != ESP_GATT_OK){
            esp_log_buffer_hex(BT_BLE_COEX_TAG, param->conf.value, param->conf.len);
        }
    break;
    case ESP_GATTS_DISCONNECT_EVT:
    case ESP_GATTS_OPEN_EVT:
    case ESP_GATTS_CANCEL_OPEN_EVT:
    case ESP_GATTS_CLOSE_EVT:
    case ESP_GATTS_LISTEN_EVT:
    case ESP_GATTS_CONGEST_EVT:
    default:
        break;
    }
}