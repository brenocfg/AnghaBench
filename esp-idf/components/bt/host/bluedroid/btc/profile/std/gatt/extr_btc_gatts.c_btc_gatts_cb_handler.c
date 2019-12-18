#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_94__   TYPE_9__ ;
typedef  struct TYPE_93__   TYPE_8__ ;
typedef  struct TYPE_92__   TYPE_7__ ;
typedef  struct TYPE_91__   TYPE_6__ ;
typedef  struct TYPE_90__   TYPE_5__ ;
typedef  struct TYPE_89__   TYPE_4__ ;
typedef  struct TYPE_88__   TYPE_45__ ;
typedef  struct TYPE_87__   TYPE_44__ ;
typedef  struct TYPE_86__   TYPE_43__ ;
typedef  struct TYPE_85__   TYPE_42__ ;
typedef  struct TYPE_84__   TYPE_41__ ;
typedef  struct TYPE_83__   TYPE_40__ ;
typedef  struct TYPE_82__   TYPE_3__ ;
typedef  struct TYPE_81__   TYPE_39__ ;
typedef  struct TYPE_80__   TYPE_38__ ;
typedef  struct TYPE_79__   TYPE_37__ ;
typedef  struct TYPE_78__   TYPE_36__ ;
typedef  struct TYPE_77__   TYPE_35__ ;
typedef  struct TYPE_76__   TYPE_34__ ;
typedef  struct TYPE_75__   TYPE_33__ ;
typedef  struct TYPE_74__   TYPE_32__ ;
typedef  struct TYPE_73__   TYPE_31__ ;
typedef  struct TYPE_72__   TYPE_30__ ;
typedef  struct TYPE_71__   TYPE_2__ ;
typedef  struct TYPE_70__   TYPE_29__ ;
typedef  struct TYPE_69__   TYPE_28__ ;
typedef  struct TYPE_68__   TYPE_27__ ;
typedef  struct TYPE_67__   TYPE_26__ ;
typedef  struct TYPE_66__   TYPE_25__ ;
typedef  struct TYPE_65__   TYPE_24__ ;
typedef  struct TYPE_64__   TYPE_23__ ;
typedef  struct TYPE_63__   TYPE_22__ ;
typedef  struct TYPE_62__   TYPE_21__ ;
typedef  struct TYPE_61__   TYPE_20__ ;
typedef  struct TYPE_60__   TYPE_1__ ;
typedef  struct TYPE_59__   TYPE_19__ ;
typedef  struct TYPE_58__   TYPE_18__ ;
typedef  struct TYPE_57__   TYPE_17__ ;
typedef  struct TYPE_56__   TYPE_16__ ;
typedef  struct TYPE_55__   TYPE_15__ ;
typedef  struct TYPE_54__   TYPE_14__ ;
typedef  struct TYPE_53__   TYPE_13__ ;
typedef  struct TYPE_52__   TYPE_12__ ;
typedef  struct TYPE_51__   TYPE_11__ ;
typedef  struct TYPE_50__   TYPE_10__ ;

/* Type definitions */
struct TYPE_85__ {int /*<<< orphan*/  status; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  service_id; int /*<<< orphan*/  server_if; } ;
struct TYPE_83__ {int /*<<< orphan*/  congested; int /*<<< orphan*/  conn_id; } ;
struct TYPE_80__ {int /*<<< orphan*/  status; int /*<<< orphan*/  server_if; } ;
struct TYPE_78__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  status; } ;
struct TYPE_76__ {int /*<<< orphan*/  status; int /*<<< orphan*/  server_if; } ;
struct TYPE_74__ {int /*<<< orphan*/  status; int /*<<< orphan*/  server_if; } ;
struct TYPE_69__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  interval; } ;
struct TYPE_72__ {int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  reason; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  server_if; TYPE_28__ conn_params; } ;
struct TYPE_66__ {int /*<<< orphan*/  service_id; int /*<<< orphan*/  status; int /*<<< orphan*/  server_if; } ;
struct TYPE_62__ {int /*<<< orphan*/  char_uuid; int /*<<< orphan*/  service_id; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  status; int /*<<< orphan*/  server_if; } ;
struct TYPE_57__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  svc_instance; int /*<<< orphan*/  is_primary; int /*<<< orphan*/  service_id; int /*<<< orphan*/  status; int /*<<< orphan*/  server_if; } ;
struct TYPE_52__ {int /*<<< orphan*/  value; int /*<<< orphan*/  data_len; int /*<<< orphan*/  status; int /*<<< orphan*/  handle; int /*<<< orphan*/  conn_id; TYPE_11__* p_data; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  trans_id; } ;
struct TYPE_71__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_82__ {TYPE_2__ uu; } ;
struct TYPE_89__ {int /*<<< orphan*/  server_if; TYPE_3__ uuid; int /*<<< orphan*/  status; } ;
struct TYPE_86__ {TYPE_42__ attr_val; TYPE_40__ congest; TYPE_38__ service_change; TYPE_36__ close; TYPE_34__ cancel_open; TYPE_32__ open; TYPE_30__ conn; TYPE_25__ srvc_oper; TYPE_21__ add_result; TYPE_17__ create; TYPE_12__ req_data; TYPE_4__ reg_oper; } ;
typedef  TYPE_43__ tBTA_GATTS ;
typedef  int /*<<< orphan*/  esp_gatt_if_t ;
struct TYPE_84__ {int /*<<< orphan*/  status; int /*<<< orphan*/  attr_handle; int /*<<< orphan*/  srvc_handle; } ;
struct TYPE_81__ {int /*<<< orphan*/  congested; void* conn_id; } ;
struct TYPE_79__ {int /*<<< orphan*/  status; } ;
struct TYPE_77__ {void* conn_id; int /*<<< orphan*/  status; } ;
struct TYPE_75__ {int /*<<< orphan*/  status; } ;
struct TYPE_73__ {int /*<<< orphan*/  status; } ;
struct TYPE_70__ {int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  reason; void* conn_id; } ;
struct TYPE_67__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  interval; } ;
struct TYPE_68__ {TYPE_26__ conn_params; int /*<<< orphan*/  remote_bda; void* conn_id; } ;
struct TYPE_65__ {int /*<<< orphan*/  service_handle; int /*<<< orphan*/  status; } ;
struct TYPE_64__ {int /*<<< orphan*/  service_handle; int /*<<< orphan*/  status; } ;
struct TYPE_63__ {int /*<<< orphan*/  service_handle; int /*<<< orphan*/  status; } ;
struct TYPE_61__ {int /*<<< orphan*/  descr_uuid; int /*<<< orphan*/  service_handle; int /*<<< orphan*/  attr_handle; int /*<<< orphan*/  status; } ;
struct TYPE_59__ {int /*<<< orphan*/  char_uuid; int /*<<< orphan*/  service_handle; int /*<<< orphan*/  attr_handle; int /*<<< orphan*/  status; } ;
struct TYPE_58__ {int /*<<< orphan*/  service_handle; int /*<<< orphan*/  attr_handle; int /*<<< orphan*/  status; } ;
struct TYPE_54__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  inst_id; } ;
struct TYPE_55__ {TYPE_14__ id; int /*<<< orphan*/  is_primary; } ;
struct TYPE_56__ {TYPE_15__ service_id; int /*<<< orphan*/  service_handle; int /*<<< orphan*/  status; } ;
struct TYPE_53__ {int /*<<< orphan*/  len; int /*<<< orphan*/  value; int /*<<< orphan*/  handle; int /*<<< orphan*/  status; void* conn_id; } ;
struct TYPE_50__ {int /*<<< orphan*/  mtu; void* conn_id; } ;
struct TYPE_94__ {int /*<<< orphan*/  exec_write_flag; int /*<<< orphan*/  bda; int /*<<< orphan*/  trans_id; void* conn_id; } ;
struct TYPE_92__ {int /*<<< orphan*/  value; int /*<<< orphan*/  len; int /*<<< orphan*/  is_prep; int /*<<< orphan*/  need_rsp; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  bda; int /*<<< orphan*/  trans_id; void* conn_id; } ;
struct TYPE_90__ {int /*<<< orphan*/  need_rsp; int /*<<< orphan*/  is_long; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  bda; int /*<<< orphan*/  trans_id; void* conn_id; } ;
struct TYPE_60__ {int /*<<< orphan*/  app_id; int /*<<< orphan*/  status; } ;
struct TYPE_87__ {TYPE_41__ set_attr_val; TYPE_39__ congest; TYPE_37__ service_change; TYPE_35__ close; TYPE_33__ cancel_open; TYPE_31__ open; TYPE_29__ disconnect; TYPE_27__ connect; TYPE_24__ stop; TYPE_23__ start; TYPE_22__ del; TYPE_20__ add_char_descr; TYPE_19__ add_char; TYPE_18__ add_incl_srvc; TYPE_16__ create; TYPE_13__ conf; TYPE_10__ mtu; TYPE_9__ exec_write; TYPE_7__ write; TYPE_5__ read; TYPE_1__ reg; } ;
typedef  TYPE_44__ esp_ble_gatts_cb_param_t ;
struct TYPE_88__ {int act; scalar_t__ arg; } ;
typedef  TYPE_45__ btc_msg_t ;
struct TYPE_93__ {int /*<<< orphan*/  value; int /*<<< orphan*/  len; int /*<<< orphan*/  is_prep; int /*<<< orphan*/  need_rsp; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct TYPE_91__ {int /*<<< orphan*/  need_rsp; int /*<<< orphan*/  is_long; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct TYPE_51__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  exec_write; TYPE_8__ write_req; TYPE_6__ read_req; } ;

/* Variables and functions */
#define  BTA_GATTS_ADD_CHAR_DESCR_EVT 150 
#define  BTA_GATTS_ADD_CHAR_EVT 149 
#define  BTA_GATTS_ADD_INCL_SRVC_EVT 148 
#define  BTA_GATTS_CANCEL_OPEN_EVT 147 
#define  BTA_GATTS_CLOSE_EVT 146 
#define  BTA_GATTS_CONF_EVT 145 
#define  BTA_GATTS_CONGEST_EVT 144 
#define  BTA_GATTS_CONNECT_EVT 143 
#define  BTA_GATTS_CREATE_EVT 142 
#define  BTA_GATTS_DELELTE_EVT 141 
#define  BTA_GATTS_DEREG_EVT 140 
#define  BTA_GATTS_DISCONNECT_EVT 139 
#define  BTA_GATTS_EXEC_WRITE_EVT 138 
#define  BTA_GATTS_LISTEN_EVT 137 
#define  BTA_GATTS_MTU_EVT 136 
#define  BTA_GATTS_OPEN_EVT 135 
#define  BTA_GATTS_READ_EVT 134 
#define  BTA_GATTS_REG_EVT 133 
#define  BTA_GATTS_SEND_SERVICE_CHANGE_EVT 132 
#define  BTA_GATTS_SET_ATTR_VAL_EVT 131 
#define  BTA_GATTS_START_EVT 130 
#define  BTA_GATTS_STOP_EVT 129 
#define  BTA_GATTS_WRITE_EVT 128 
 void* BTC_GATT_GET_CONN_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTC_GATT_GET_GATT_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BD_ADDR_LEN ; 
 int const ESP_GATTS_ADD_CHAR_DESCR_EVT ; 
 int const ESP_GATTS_ADD_CHAR_EVT ; 
 int const ESP_GATTS_ADD_INCL_SRVC_EVT ; 
 int const ESP_GATTS_CONF_EVT ; 
 int const ESP_GATTS_CONGEST_EVT ; 
 int const ESP_GATTS_CONNECT_EVT ; 
 int const ESP_GATTS_CREATE_EVT ; 
 int const ESP_GATTS_DELETE_EVT ; 
 int const ESP_GATTS_DISCONNECT_EVT ; 
 int const ESP_GATTS_EXEC_WRITE_EVT ; 
 int const ESP_GATTS_MTU_EVT ; 
 int const ESP_GATTS_READ_EVT ; 
 int const ESP_GATTS_REG_EVT ; 
 int const ESP_GATTS_SEND_SERVICE_CHANGE_EVT ; 
 int const ESP_GATTS_SET_ATTR_VAL_EVT ; 
 int const ESP_GATTS_START_EVT ; 
 int const ESP_GATTS_STOP_EVT ; 
 int const ESP_GATTS_UNREG_EVT ; 
 int const ESP_GATTS_WRITE_EVT ; 
 int /*<<< orphan*/  ESP_GATT_OK ; 
 int /*<<< orphan*/  bta_to_btc_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btc_gatts_cb_param_copy_free (TYPE_45__*,TYPE_43__*) ; 
 int /*<<< orphan*/  btc_gatts_cb_to_app (int const,int /*<<< orphan*/ ,TYPE_44__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btc_gatts_cb_handler(btc_msg_t *msg)
{
    esp_ble_gatts_cb_param_t param;
    tBTA_GATTS *p_data = (tBTA_GATTS *)msg->arg;
    esp_gatt_if_t gatts_if;

    switch (msg->act) {
    case BTA_GATTS_REG_EVT: {
        gatts_if = p_data->reg_oper.server_if;
        param.reg.status = p_data->reg_oper.status;
        param.reg.app_id = p_data->reg_oper.uuid.uu.uuid16;

        btc_gatts_cb_to_app(ESP_GATTS_REG_EVT, gatts_if, &param);
        break;
    }
    case BTA_GATTS_DEREG_EVT: {
        gatts_if = p_data->reg_oper.server_if;
        btc_gatts_cb_to_app(ESP_GATTS_UNREG_EVT, gatts_if, NULL);
        break;
    }
    case BTA_GATTS_READ_EVT: {
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.read.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.read.trans_id = p_data->req_data.trans_id;
        memcpy(param.read.bda, p_data->req_data.remote_bda, ESP_BD_ADDR_LEN);
        param.read.handle = p_data->req_data.p_data->read_req.handle;
        param.read.offset = p_data->req_data.p_data->read_req.offset;
        param.read.is_long = p_data->req_data.p_data->read_req.is_long;

        param.read.need_rsp = p_data->req_data.p_data->read_req.need_rsp;
        btc_gatts_cb_to_app(ESP_GATTS_READ_EVT, gatts_if, &param);
        break;
    }
    case BTA_GATTS_WRITE_EVT: {
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.write.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.write.trans_id = p_data->req_data.trans_id;
        memcpy(param.write.bda, p_data->req_data.remote_bda, ESP_BD_ADDR_LEN);
        if (p_data->req_data.p_data == NULL) {
            break;
        }
        param.write.handle = p_data->req_data.p_data->write_req.handle;
        param.write.offset = p_data->req_data.p_data->write_req.offset;
        param.write.need_rsp = p_data->req_data.p_data->write_req.need_rsp;
        param.write.is_prep = p_data->req_data.p_data->write_req.is_prep;
        param.write.len = p_data->req_data.p_data->write_req.len;
        param.write.value = p_data->req_data.p_data->write_req.value;

        btc_gatts_cb_to_app(ESP_GATTS_WRITE_EVT, gatts_if, &param);

        break;
    }
    case BTA_GATTS_EXEC_WRITE_EVT: {
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.exec_write.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.exec_write.trans_id = p_data->req_data.trans_id;
        memcpy(param.exec_write.bda, p_data->req_data.remote_bda, ESP_BD_ADDR_LEN);
        if (p_data->req_data.p_data == NULL) {
            break;
        }
        param.exec_write.exec_write_flag = p_data->req_data.p_data->exec_write;

        btc_gatts_cb_to_app(ESP_GATTS_EXEC_WRITE_EVT, gatts_if, &param);
        break;
    }
    case BTA_GATTS_MTU_EVT:
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.mtu.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.mtu.mtu = p_data->req_data.p_data->mtu;

        btc_gatts_cb_to_app(ESP_GATTS_MTU_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_CONF_EVT:
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.conf.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.conf.status = p_data->req_data.status;
        param.conf.handle = p_data->req_data.handle;

        if (p_data->req_data.status != ESP_GATT_OK && p_data->req_data.value){
            param.conf.len = p_data->req_data.data_len;
            param.conf.value = p_data->req_data.value;
        }else{
            param.conf.len = 0;
        }
        btc_gatts_cb_to_app(ESP_GATTS_CONF_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_CREATE_EVT:
        gatts_if = p_data->create.server_if;
        param.create.status = p_data->create.status;
        param.create.service_handle = p_data->create.service_id;
        param.create.service_id.is_primary = p_data->create.is_primary;
        param.create.service_id.id.inst_id = p_data->create.svc_instance;
        bta_to_btc_uuid(&param.create.service_id.id.uuid, &p_data->create.uuid);

        btc_gatts_cb_to_app(ESP_GATTS_CREATE_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_ADD_INCL_SRVC_EVT:
        gatts_if = p_data->add_result.server_if;
        param.add_incl_srvc.status = p_data->add_result.status;
        param.add_incl_srvc.attr_handle = p_data->add_result.attr_id;
        param.add_incl_srvc.service_handle = p_data->add_result.service_id;

        btc_gatts_cb_to_app(ESP_GATTS_ADD_INCL_SRVC_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_ADD_CHAR_EVT:
        gatts_if = p_data->add_result.server_if;
        param.add_char.status = p_data->add_result.status;
        param.add_char.attr_handle = p_data->add_result.attr_id;
        param.add_char.service_handle = p_data->add_result.service_id;
        bta_to_btc_uuid(&param.add_char.char_uuid, &p_data->add_result.char_uuid);

        btc_gatts_cb_to_app(ESP_GATTS_ADD_CHAR_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_ADD_CHAR_DESCR_EVT:
        gatts_if = p_data->add_result.server_if;
        param.add_char_descr.status = p_data->add_result.status;
        param.add_char_descr.attr_handle = p_data->add_result.attr_id;
        param.add_char_descr.service_handle = p_data->add_result.service_id;
        bta_to_btc_uuid(&param.add_char_descr.descr_uuid, &p_data->add_result.char_uuid);

        btc_gatts_cb_to_app(ESP_GATTS_ADD_CHAR_DESCR_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_DELELTE_EVT:
        gatts_if = p_data->srvc_oper.server_if;
        param.del.status = p_data->srvc_oper.status;
        param.del.service_handle = p_data->srvc_oper.service_id;

        btc_gatts_cb_to_app(ESP_GATTS_DELETE_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_START_EVT:
        gatts_if = p_data->srvc_oper.server_if;
        param.start.status = p_data->srvc_oper.status;
        param.start.service_handle = p_data->srvc_oper.service_id;

        btc_gatts_cb_to_app(ESP_GATTS_START_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_STOP_EVT:
        gatts_if = p_data->srvc_oper.server_if;
        param.stop.status = p_data->srvc_oper.status;
        param.stop.service_handle = p_data->srvc_oper.service_id;

        btc_gatts_cb_to_app(ESP_GATTS_STOP_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_CONNECT_EVT:
        gatts_if = p_data->conn.server_if;
        param.connect.conn_id = BTC_GATT_GET_CONN_ID(p_data->conn.conn_id);
        memcpy(param.connect.remote_bda, p_data->conn.remote_bda, ESP_BD_ADDR_LEN);
        param.connect.conn_params.interval = p_data->conn.conn_params.interval;
        param.connect.conn_params.latency = p_data->conn.conn_params.latency;
        param.connect.conn_params.timeout = p_data->conn.conn_params.timeout;
        btc_gatts_cb_to_app(ESP_GATTS_CONNECT_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_DISCONNECT_EVT:
        gatts_if = p_data->conn.server_if;
        param.disconnect.conn_id = BTC_GATT_GET_CONN_ID(p_data->conn.conn_id);
        param.disconnect.reason = p_data->conn.reason;
        memcpy(param.disconnect.remote_bda, p_data->conn.remote_bda, ESP_BD_ADDR_LEN);

        btc_gatts_cb_to_app(ESP_GATTS_DISCONNECT_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_OPEN_EVT:
        gatts_if = p_data->open.server_if;
        param.open.status = p_data->open.status;

        btc_gatts_cb_to_app(BTA_GATTS_OPEN_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_CANCEL_OPEN_EVT:
        gatts_if = p_data->cancel_open.server_if;
        param.cancel_open.status = p_data->cancel_open.status;

        btc_gatts_cb_to_app(BTA_GATTS_CANCEL_OPEN_EVT, gatts_if, &param);
        break;

    case BTA_GATTS_CLOSE_EVT:
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->close.conn_id);
        param.close.status = p_data->close.status;
        param.close.conn_id = BTC_GATT_GET_CONN_ID(p_data->close.conn_id);

        btc_gatts_cb_to_app(BTA_GATTS_CLOSE_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_SEND_SERVICE_CHANGE_EVT:
        gatts_if = p_data->service_change.server_if;
        param.service_change.status = p_data->service_change.status;
        btc_gatts_cb_to_app(ESP_GATTS_SEND_SERVICE_CHANGE_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_LISTEN_EVT:
        // do nothing
        break;
    case BTA_GATTS_CONGEST_EVT:
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->congest.conn_id);
        param.congest.conn_id = BTC_GATT_GET_CONN_ID(p_data->congest.conn_id);
        param.congest.congested = p_data->congest.congested;
        btc_gatts_cb_to_app(ESP_GATTS_CONGEST_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_SET_ATTR_VAL_EVT:
        gatts_if = p_data->attr_val.server_if;
        param.set_attr_val.srvc_handle = p_data->attr_val.service_id;
        param.set_attr_val.attr_handle = p_data->attr_val.attr_id;
        param.set_attr_val.status = p_data->attr_val.status;
        btc_gatts_cb_to_app(ESP_GATTS_SET_ATTR_VAL_EVT, gatts_if, &param);
        break;
    default:
        // do nothing
        break;
    }

    btc_gatts_cb_param_copy_free(msg, p_data);
}