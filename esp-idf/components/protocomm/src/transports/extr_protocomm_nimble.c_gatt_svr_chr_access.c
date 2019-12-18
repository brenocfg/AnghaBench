#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct ble_gatt_access_ctxt {int op; int /*<<< orphan*/  om; TYPE_1__* chr; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int /*<<< orphan*/  pc_ble; } ;
struct TYPE_3__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int BLE_ATT_ERR_INSUFFICIENT_RES ; 
 int BLE_ATT_ERR_INVALID_PDU ; 
 int BLE_ATT_ERR_UNLIKELY ; 
#define  BLE_GATT_ACCESS_OP_READ_CHR 129 
#define  BLE_GATT_ACCESS_OP_WRITE_CHR 128 
 int BLE_UUID128_VAL_LENGTH ; 
 int BLE_UUID_STR_LEN ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int OS_MBUF_PKTLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int ble_hs_mbuf_to_flat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int ble_uuid_flat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ble_uuid_to_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int os_mbuf_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* protoble_internal ; 
 int /*<<< orphan*/  protocomm_req_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int simple_ble_gatts_get_attr_value (int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int simple_ble_gatts_set_attr_value (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid128_to_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gatt_svr_chr_access(uint16_t conn_handle, uint16_t attr_handle,
                    struct ble_gatt_access_ctxt *ctxt,
                    void *arg)
{
    int rc;
    esp_err_t ret;
    char buf[BLE_UUID_STR_LEN];
    ssize_t temp_outlen = 0;
    uint8_t *temp_outbuf = NULL;
    uint8_t *uuid = NULL;
    uint8_t *data_buf = NULL;
    uint16_t data_len = 0;
    uint16_t data_buf_len = 0;

    switch (ctxt->op) {
    case BLE_GATT_ACCESS_OP_READ_CHR:
        ESP_LOGD(TAG, "Read attempeted for Characterstic UUID = %s, attr_handle = %d",
                 ble_uuid_to_str(ctxt->chr->uuid, buf), attr_handle);

        rc = simple_ble_gatts_get_attr_value(attr_handle, &temp_outlen,
                                             &temp_outbuf);
        if (rc != 0) {
            ESP_LOGE(TAG, "Failed to read characteristic with attr_handle = %d", attr_handle);
            return rc;
        }

        rc = os_mbuf_append(ctxt->om, temp_outbuf, temp_outlen);
        return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;

    case BLE_GATT_ACCESS_OP_WRITE_CHR:
        uuid = (uint8_t *) calloc(BLE_UUID128_VAL_LENGTH, sizeof(uint8_t));
        if (!uuid) {
            ESP_LOGE(TAG, "Error allocating memory for 128 bit UUID");
            return BLE_ATT_ERR_INSUFFICIENT_RES;
        }

        rc = ble_uuid_flat(ctxt->chr->uuid, uuid);
        if (rc != 0) {
            free(uuid);
            ESP_LOGE(TAG, "Error fetching Characteristic UUID128");
            return rc;
        }

        /* Save the length of entire data */
        data_len = OS_MBUF_PKTLEN(ctxt->om);
        ESP_LOGD(TAG, "Write attempt for uuid = %s, attr_handle = %d, data_len = %d",
                 ble_uuid_to_str(ctxt->chr->uuid, buf), attr_handle, data_len);

        data_buf = calloc(1, data_len);
        if (data_buf == NULL) {
            ESP_LOGE(TAG, "Error allocating memory for characteristic value");
            return BLE_ATT_ERR_INSUFFICIENT_RES;
        }

        rc = ble_hs_mbuf_to_flat(ctxt->om, data_buf, data_len, &data_buf_len);
        if (rc != 0) {
            ESP_LOGE(TAG, "Error getting data from memory buffers");
            return BLE_ATT_ERR_UNLIKELY;
        }

        ret = protocomm_req_handle(protoble_internal->pc_ble,
                                   uuid128_to_handler(uuid),
                                   conn_handle,
                                   data_buf,
                                   data_buf_len,
                                   &temp_outbuf, &temp_outlen);
        /* Release the 16 bytes allocated for uuid*/
        free(uuid);
        free(data_buf);
        if (ret == ESP_OK) {

            /* Save data address and length outbuf and outlen internally */
            rc = simple_ble_gatts_set_attr_value(attr_handle, temp_outlen,
                                                 temp_outbuf);
            if (rc != 0) {
                ESP_LOGE(TAG, "Failed to set outbuf for characteristic with attr_handle = %d",
                         attr_handle);
                free(temp_outbuf);
            }

            return rc;
        } else {
            ESP_LOGE(TAG, "Invalid content received, killing connection");
            return BLE_ATT_ERR_INVALID_PDU;
        }

    default:
        return BLE_ATT_ERR_UNLIKELY;
    }
}