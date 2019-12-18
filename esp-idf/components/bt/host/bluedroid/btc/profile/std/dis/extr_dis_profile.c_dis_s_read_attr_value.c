#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ len; scalar_t__* value; } ;
typedef  TYPE_4__ tGATT_VALUE ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
struct TYPE_17__ {TYPE_4__ attr_value; } ;
typedef  TYPE_5__ tGATTS_RSP ;
struct TYPE_13__ {scalar_t__ offset; scalar_t__ handle; int is_long; } ;
struct TYPE_18__ {TYPE_1__ read_req; } ;
typedef  TYPE_6__ tGATTS_DATA ;
struct TYPE_19__ {scalar_t__ handle; int uuid; } ;
typedef  TYPE_7__ tDIS_DB_ENTRY ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_14__ {int /*<<< orphan*/  product_version; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  vendor_id_src; } ;
struct TYPE_15__ {TYPE_2__ pnp_id; int /*<<< orphan*/  system_id; scalar_t__** data_string; } ;
struct TYPE_12__ {TYPE_3__ dis_value; TYPE_7__* dis_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ DIS_MAX_CHAR_NUM ; 
 scalar_t__ DIS_PNP_ID_SIZE ; 
 scalar_t__ DIS_SYSTEM_ID_SIZE ; 
 int /*<<< orphan*/  ESP_GATT_INVALID_OFFSET ; 
 int /*<<< orphan*/  ESP_GATT_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_GATT_NOT_LONG ; 
 scalar_t__ GATT_MAX_ATTR_LEN ; 
 int /*<<< orphan*/  GATT_TRACE_EVENT (char*,scalar_t__) ; 
#define  GATT_UUID_FW_VERSION_STR 136 
#define  GATT_UUID_HW_VERSION_STR 135 
#define  GATT_UUID_IEEE_DATA 134 
#define  GATT_UUID_MANU_NAME 133 
#define  GATT_UUID_MODEL_NUMBER_STR 132 
#define  GATT_UUID_PNP_ID 131 
#define  GATT_UUID_SERIAL_NUMBER_STR 130 
#define  GATT_UUID_SW_VERSION_STR 129 
#define  GATT_UUID_SYSTEM_ID 128 
 int TRUE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64_TO_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_11__ dis_cb ; 
 int /*<<< orphan*/  esp_ble_gatts_send_rsp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ strlen (char*) ; 

void dis_s_read_attr_value (tGATTS_DATA *p_data, tGATT_VALUE *p_value, UINT32 trans_id, UINT16 conn_id)
{
    tDIS_DB_ENTRY   *p_db_attr = dis_cb.dis_attr;
    UINT8           *p = p_value->value, i, *pp;
    UINT16          offset = p_data->read_req.offset;
    tGATT_STATUS    st = ESP_GATT_NOT_FOUND;
    UINT16          handle = p_data->read_req.handle;
    bool            is_long = p_data->read_req.is_long;

    for (i = 0; i < DIS_MAX_CHAR_NUM; i ++, p_db_attr ++) {
        if (handle == p_db_attr->handle) {
            if ((p_db_attr->uuid == GATT_UUID_PNP_ID || p_db_attr->uuid == GATT_UUID_SYSTEM_ID) &&
                    is_long == TRUE) {
                st = ESP_GATT_NOT_LONG;
                break;
            }
            st = ESP_GATT_NOT_FOUND;

            switch (p_db_attr->uuid) {
            case GATT_UUID_MANU_NAME:
            case GATT_UUID_MODEL_NUMBER_STR:
            case GATT_UUID_SERIAL_NUMBER_STR:
            case GATT_UUID_FW_VERSION_STR:
            case GATT_UUID_HW_VERSION_STR:
            case GATT_UUID_SW_VERSION_STR:
            case GATT_UUID_IEEE_DATA:
                pp = dis_cb.dis_value.data_string[p_db_attr->uuid - GATT_UUID_MODEL_NUMBER_STR];
                if (pp != NULL) {
                    if (strlen ((char *)pp) > GATT_MAX_ATTR_LEN) {
                        p_value->len = GATT_MAX_ATTR_LEN;
                    } else {
                        p_value->len = (UINT16)strlen ((char *)pp);
                    }
                } else {
                    p_value->len = 0;
                }

                if (offset > p_value->len) {
                    st = ESP_GATT_INVALID_OFFSET;
                    break;
                } else {
                    p_value->len -= offset;
                    pp += offset;
                    ARRAY_TO_STREAM(p, pp, p_value->len);
                    GATT_TRACE_EVENT("GATT_UUID_MANU_NAME len=0x%04x", p_value->len);
                }
                break;


            case GATT_UUID_SYSTEM_ID:
                UINT64_TO_STREAM(p, dis_cb.dis_value.system_id); /* int_min */
                p_value->len = DIS_SYSTEM_ID_SIZE;
                break;

            case  GATT_UUID_PNP_ID:
                UINT8_TO_STREAM(p, dis_cb.dis_value.pnp_id.vendor_id_src);
                UINT16_TO_STREAM(p, dis_cb.dis_value.pnp_id.vendor_id);
                UINT16_TO_STREAM(p, dis_cb.dis_value.pnp_id.product_id);
                UINT16_TO_STREAM(p, dis_cb.dis_value.pnp_id.product_version);
                p_value->len = DIS_PNP_ID_SIZE;
                break;

            }
            break;
        }
    }
    tGATTS_RSP       rsp;
    rsp.attr_value = *p_value;
    esp_ble_gatts_send_rsp(conn_id, trans_id, st, &rsp);

}