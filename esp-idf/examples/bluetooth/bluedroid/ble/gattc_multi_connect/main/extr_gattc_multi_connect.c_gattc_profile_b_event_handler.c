#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  write_char_data ;
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  notify_en ;
struct TYPE_35__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_36__ {TYPE_3__ uuid; int /*<<< orphan*/  len; } ;
struct TYPE_30__ {int properties; int /*<<< orphan*/  handle; TYPE_4__ uuid; int /*<<< orphan*/  char_handle; } ;
typedef  TYPE_15__ esp_gattc_descr_elem_t ;
typedef  TYPE_15__ esp_gattc_char_elem_t ;
typedef  int esp_gattc_cb_event_t ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;
typedef  int /*<<< orphan*/  esp_gatt_if_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_40__ {int /*<<< orphan*/  remote_bda; } ;
struct TYPE_39__ {int /*<<< orphan*/  remote_bda; } ;
struct TYPE_38__ {int /*<<< orphan*/  status; } ;
struct TYPE_37__ {int value_len; int /*<<< orphan*/  value; } ;
struct TYPE_34__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  status; } ;
struct TYPE_33__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  status; } ;
struct TYPE_26__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_27__ {TYPE_11__ uuid; int /*<<< orphan*/  len; } ;
struct TYPE_28__ {TYPE_12__ uuid; int /*<<< orphan*/  inst_id; } ;
struct TYPE_29__ {int /*<<< orphan*/  end_handle; int /*<<< orphan*/  start_handle; TYPE_13__ srvc_id; int /*<<< orphan*/  is_primary; int /*<<< orphan*/  conn_id; } ;
struct TYPE_25__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  mtu; int /*<<< orphan*/  status; } ;
struct TYPE_41__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  mtu; int /*<<< orphan*/  status; } ;
struct TYPE_31__ {TYPE_8__ disconnect; TYPE_7__ srvc_chg; TYPE_6__ write; TYPE_5__ notify; TYPE_2__ reg_for_notify; TYPE_1__ search_cmpl; TYPE_14__ search_res; TYPE_10__ cfg_mtu; TYPE_9__ open; } ;
typedef  TYPE_17__ esp_ble_gattc_cb_param_t ;
typedef  int* esp_bd_addr_t ;
struct TYPE_32__ {int* remote_bda; int /*<<< orphan*/  char_handle; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  service_end_handle; int /*<<< orphan*/  service_start_handle; } ;

/* Variables and functions */
#define  ESP_GATTC_CFG_MTU_EVT 139 
#define  ESP_GATTC_CONNECT_EVT 138 
#define  ESP_GATTC_DISCONNECT_EVT 137 
#define  ESP_GATTC_NOTIFY_EVT 136 
#define  ESP_GATTC_OPEN_EVT 135 
#define  ESP_GATTC_REG_EVT 134 
#define  ESP_GATTC_REG_FOR_NOTIFY_EVT 133 
#define  ESP_GATTC_SEARCH_CMPL_EVT 132 
#define  ESP_GATTC_SEARCH_RES_EVT 131 
#define  ESP_GATTC_SRVC_CHG_EVT 130 
#define  ESP_GATTC_WRITE_CHAR_EVT 129 
#define  ESP_GATTC_WRITE_DESCR_EVT 128 
 int /*<<< orphan*/  ESP_GATT_AUTH_REQ_NONE ; 
 int ESP_GATT_CHAR_PROP_BIT_NOTIFY ; 
 int /*<<< orphan*/  ESP_GATT_DB_CHARACTERISTIC ; 
 int /*<<< orphan*/  ESP_GATT_DB_DESCRIPTOR ; 
 int /*<<< orphan*/  ESP_GATT_OK ; 
 int /*<<< orphan*/  ESP_GATT_UUID_CHAR_CLIENT_CONFIG ; 
 int /*<<< orphan*/  ESP_GATT_WRITE_TYPE_RSP ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_UUID_LEN_16 ; 
 int /*<<< orphan*/  GATTC_TAG ; 
 int /*<<< orphan*/  INVALID_HANDLE ; 
 size_t PROFILE_B_APP_ID ; 
 int /*<<< orphan*/  REMOTE_SERVICE_UUID ; 
 TYPE_15__* char_elem_result_b ; 
 int conn_device_b ; 
 TYPE_15__* descr_elem_result_b ; 
 int /*<<< orphan*/  esp_ble_gattc_get_attr_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  esp_ble_gattc_get_char_by_uuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_15__*,int*) ; 
 int /*<<< orphan*/  esp_ble_gattc_get_descr_by_char_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_15__*,int*) ; 
 int /*<<< orphan*/  esp_ble_gattc_register_for_notify (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_gattc_search_service (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_ble_gattc_send_mtu_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_gattc_write_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_gattc_write_char_descr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (TYPE_15__*) ; 
 int get_service_b ; 
 TYPE_18__* gl_profile_tab ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notify_descr_uuid ; 
 int /*<<< orphan*/  remote_filter_char_uuid ; 
 int /*<<< orphan*/  remote_filter_service_uuid ; 
 int /*<<< orphan*/  start_scan () ; 

__attribute__((used)) static void gattc_profile_b_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{
    esp_ble_gattc_cb_param_t *p_data = (esp_ble_gattc_cb_param_t *)param;

    switch (event) {
    case ESP_GATTC_REG_EVT:
        ESP_LOGI(GATTC_TAG, "REG_EVT");
        break;
    case ESP_GATTC_CONNECT_EVT:
        break;
    case ESP_GATTC_OPEN_EVT:
        if (p_data->open.status != ESP_GATT_OK){
            //open failed, ignore the second device, connect the third device
            ESP_LOGE(GATTC_TAG, "connect device failed, status %d", p_data->open.status);
            conn_device_b = false;
            //start_scan();
            break;
        }
        memcpy(gl_profile_tab[PROFILE_B_APP_ID].remote_bda, p_data->open.remote_bda, 6);
        gl_profile_tab[PROFILE_B_APP_ID].conn_id = p_data->open.conn_id;
        ESP_LOGI(GATTC_TAG, "ESP_GATTC_OPEN_EVT conn_id %d, if %d, status %d, mtu %d", p_data->open.conn_id, gattc_if, p_data->open.status, p_data->open.mtu);
        ESP_LOGI(GATTC_TAG, "REMOTE BDA:");
        esp_log_buffer_hex(GATTC_TAG, p_data->open.remote_bda, sizeof(esp_bd_addr_t));
        esp_err_t mtu_ret = esp_ble_gattc_send_mtu_req (gattc_if, p_data->open.conn_id);
        if (mtu_ret){
            ESP_LOGE(GATTC_TAG, "config MTU error, error code = %x", mtu_ret);
        }
        break;
    case ESP_GATTC_CFG_MTU_EVT:
        if (param->cfg_mtu.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG,"Config mtu failed");
        }
        ESP_LOGI(GATTC_TAG, "Status %d, MTU %d, conn_id %d", param->cfg_mtu.status, param->cfg_mtu.mtu, param->cfg_mtu.conn_id);
        esp_ble_gattc_search_service(gattc_if, param->cfg_mtu.conn_id, &remote_filter_service_uuid);
        break;
    case ESP_GATTC_SEARCH_RES_EVT: {
        ESP_LOGI(GATTC_TAG, "SEARCH RES: conn_id = %x is primary service %d", p_data->search_res.conn_id, p_data->search_res.is_primary);
        ESP_LOGI(GATTC_TAG, "start handle %d end handle %d current handle value %d", p_data->search_res.start_handle, p_data->search_res.end_handle, p_data->search_res.srvc_id.inst_id);
        if (p_data->search_res.srvc_id.uuid.len == ESP_UUID_LEN_16 && p_data->search_res.srvc_id.uuid.uuid.uuid16 == REMOTE_SERVICE_UUID) {
            ESP_LOGI(GATTC_TAG, "UUID16: %x", p_data->search_res.srvc_id.uuid.uuid.uuid16);
            get_service_b = true;
            gl_profile_tab[PROFILE_B_APP_ID].service_start_handle = p_data->search_res.start_handle;
            gl_profile_tab[PROFILE_B_APP_ID].service_end_handle = p_data->search_res.end_handle;
        }
        break;
    }
    case ESP_GATTC_SEARCH_CMPL_EVT:
        if (p_data->search_cmpl.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "search service failed, error status = %x", p_data->search_cmpl.status);
            break;
        }
        if (get_service_b){
            uint16_t count = 0;
            esp_gatt_status_t status = esp_ble_gattc_get_attr_count( gattc_if,
                                                                     p_data->search_cmpl.conn_id,
                                                                     ESP_GATT_DB_CHARACTERISTIC,
                                                                     gl_profile_tab[PROFILE_B_APP_ID].service_start_handle,
                                                                     gl_profile_tab[PROFILE_B_APP_ID].service_end_handle,
                                                                     INVALID_HANDLE,
                                                                     &count);
            if (status != ESP_GATT_OK){
                ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_attr_count error");
            }

            if (count > 0){
                char_elem_result_b = (esp_gattc_char_elem_t *)malloc(sizeof(esp_gattc_char_elem_t) * count);
                if (!char_elem_result_b){
                    ESP_LOGE(GATTC_TAG, "gattc no mem");
                }else{
                    status = esp_ble_gattc_get_char_by_uuid( gattc_if,
                                                             p_data->search_cmpl.conn_id,
                                                             gl_profile_tab[PROFILE_B_APP_ID].service_start_handle,
                                                             gl_profile_tab[PROFILE_B_APP_ID].service_end_handle,
                                                             remote_filter_char_uuid,
                                                             char_elem_result_b,
                                                             &count);
                    if (status != ESP_GATT_OK){
                        ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_char_by_uuid error");
                    }

                    /*  Every service have only one char in our 'ESP_GATTS_DEMO' demo, so we used first 'char_elem_result' */
                    if (count > 0 && (char_elem_result_b[0].properties & ESP_GATT_CHAR_PROP_BIT_NOTIFY)){
                        gl_profile_tab[PROFILE_B_APP_ID].char_handle = char_elem_result_b[0].char_handle;
                        esp_ble_gattc_register_for_notify (gattc_if, gl_profile_tab[PROFILE_B_APP_ID].remote_bda, char_elem_result_b[0].char_handle);
                    }
                }
                /* free char_elem_result */
                free(char_elem_result_b);
            }else{
                ESP_LOGE(GATTC_TAG, "no char found");
            }
        }
        break;
    case ESP_GATTC_REG_FOR_NOTIFY_EVT: {

        if (p_data->reg_for_notify.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "reg notify failed, error status =%x", p_data->reg_for_notify.status);
            break;
        }
        uint16_t count = 0;
        uint16_t notify_en = 1;
        esp_gatt_status_t ret_status = esp_ble_gattc_get_attr_count( gattc_if,
                                                                     gl_profile_tab[PROFILE_B_APP_ID].conn_id,
                                                                     ESP_GATT_DB_DESCRIPTOR,
                                                                     gl_profile_tab[PROFILE_B_APP_ID].service_start_handle,
                                                                     gl_profile_tab[PROFILE_B_APP_ID].service_end_handle,
                                                                     gl_profile_tab[PROFILE_B_APP_ID].char_handle,
                                                                     &count);
        if (ret_status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_attr_count error");
        }
        if (count > 0){
            descr_elem_result_b = (esp_gattc_descr_elem_t *)malloc(sizeof(esp_gattc_descr_elem_t) * count);
            if (!descr_elem_result_b){
                ESP_LOGE(GATTC_TAG, "malloc error, gattc no mem");
            }else{
                ret_status = esp_ble_gattc_get_descr_by_char_handle( gattc_if,
                                                                     gl_profile_tab[PROFILE_B_APP_ID].conn_id,
                                                                     p_data->reg_for_notify.handle,
                                                                     notify_descr_uuid,
                                                                     descr_elem_result_b,
                                                                     &count);
                if (ret_status != ESP_GATT_OK){
                    ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_descr_by_char_handle error");
                }

                /* Every char has only one descriptor in our 'ESP_GATTS_DEMO' demo, so we used first 'descr_elem_result' */
                if (count > 0 && descr_elem_result_b[0].uuid.len == ESP_UUID_LEN_16 && descr_elem_result_b[0].uuid.uuid.uuid16 == ESP_GATT_UUID_CHAR_CLIENT_CONFIG){
                    ret_status = esp_ble_gattc_write_char_descr( gattc_if,
                                                                 gl_profile_tab[PROFILE_B_APP_ID].conn_id,
                                                                 descr_elem_result_b[0].handle,
                                                                 sizeof(notify_en),
                                                                 (uint8_t *)&notify_en,
                                                                 ESP_GATT_WRITE_TYPE_RSP,
                                                                 ESP_GATT_AUTH_REQ_NONE);
                }

                if (ret_status != ESP_GATT_OK){
                    ESP_LOGE(GATTC_TAG, "esp_ble_gattc_write_char_descr error");
                }

                /* free descr_elem_result */
                free(descr_elem_result_b);
            }
        }
        else{
            ESP_LOGE(GATTC_TAG, "decsr not found");
        }
        break;
    }
    case ESP_GATTC_NOTIFY_EVT:
        ESP_LOGI(GATTC_TAG, "ESP_GATTC_NOTIFY_EVT, Receive notify value:");
        esp_log_buffer_hex(GATTC_TAG, p_data->notify.value, p_data->notify.value_len);
        break;
    case ESP_GATTC_WRITE_DESCR_EVT:
        if (p_data->write.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "write descr failed, error status = %x", p_data->write.status);
            break;
        }
        ESP_LOGI(GATTC_TAG, "write descr success");
        uint8_t write_char_data[35];
        for (int i = 0; i < sizeof(write_char_data); ++i)
        {
            write_char_data[i] = i % 256;
        }
        esp_ble_gattc_write_char( gattc_if,
                                  gl_profile_tab[PROFILE_B_APP_ID].conn_id,
                                  gl_profile_tab[PROFILE_B_APP_ID].char_handle,
                                  sizeof(write_char_data),
                                  write_char_data,
                                  ESP_GATT_WRITE_TYPE_RSP,
                                  ESP_GATT_AUTH_REQ_NONE);
        break;
    case ESP_GATTC_WRITE_CHAR_EVT:
        if (p_data->write.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "Write char failed, error status = %x", p_data->write.status);
        }else{
            ESP_LOGI(GATTC_TAG, "Write char success");
        }
        start_scan();
        break;
    case ESP_GATTC_SRVC_CHG_EVT: {
        esp_bd_addr_t bda;
        memcpy(bda, p_data->srvc_chg.remote_bda, sizeof(esp_bd_addr_t));
        ESP_LOGI(GATTC_TAG, "ESP_GATTC_SRVC_CHG_EVT, bd_addr:%08x%04x",(bda[0] << 24) + (bda[1] << 16) + (bda[2] << 8) + bda[3],
                 (bda[4] << 8) + bda[5]);
        break;
    }
    case ESP_GATTC_DISCONNECT_EVT:
        if (memcmp(p_data->disconnect.remote_bda, gl_profile_tab[PROFILE_B_APP_ID].remote_bda, 6) == 0){
            ESP_LOGI(GATTC_TAG, "device b disconnect");
            conn_device_b = false;
            get_service_b = false;
        }
        break;
    default:
        break;
    }
}