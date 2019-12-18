#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct bt_mesh_adv_param {int options; int /*<<< orphan*/  interval_max; int /*<<< orphan*/  interval_min; } ;
struct bt_mesh_adv_data {int dummy; } ;
struct ble_gap_adv_params {void* disc_mode; void* conn_mode; int /*<<< orphan*/  itvl_max; int /*<<< orphan*/  itvl_min; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 void* BLE_GAP_CONN_MODE_NON ; 
 void* BLE_GAP_CONN_MODE_UND ; 
 void* BLE_GAP_DISC_MODE_GEN ; 
 void* BLE_GAP_DISC_MODE_NON ; 
 int BLE_HS_ADV_MAX_SZ ; 
 int /*<<< orphan*/  BLE_HS_FOREVER ; 
 int BLE_MESH_ADV_OPT_CONNECTABLE ; 
 int BLE_MESH_ADV_OPT_ONE_TIME ; 
 int /*<<< orphan*/  BLE_MESH_DEV_ADVERTISING ; 
 int /*<<< orphan*/  BLE_MESH_DEV_KEEP_ADVERTISING ; 
 int /*<<< orphan*/  BLE_OWN_ADDR_PUBLIC ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int EALREADY ; 
 int ble_gap_adv_rsp_set_data (scalar_t__*,scalar_t__) ; 
 int ble_gap_adv_set_data (scalar_t__*,scalar_t__) ; 
 int ble_gap_adv_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ble_gap_adv_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_mesh_atomic_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_atomic_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ bt_mesh_dev ; 
 int /*<<< orphan*/  gap_event_cb ; 
 int /*<<< orphan*/  memset (struct ble_gap_adv_params*,int /*<<< orphan*/ ,int) ; 
 int set_ad (struct bt_mesh_adv_data const*,size_t,scalar_t__*,scalar_t__*) ; 

int bt_le_adv_start(const struct bt_mesh_adv_param *param,
                    const struct bt_mesh_adv_data *ad, size_t ad_len,
                    const struct bt_mesh_adv_data *sd, size_t sd_len)
{
#if BLE_MESH_DEV
    if (bt_mesh_atomic_test_bit(bt_mesh_dev.flags, BLE_MESH_DEV_ADVERTISING)) {
        return -EALREADY;
    }
#endif
    uint8_t buf[BLE_HS_ADV_MAX_SZ];
    uint8_t buf_len = 0;
    int err;
    struct ble_gap_adv_params adv_params;

    err = set_ad(ad, ad_len, buf, &buf_len);
    if (err) {
        BT_ERR("set_ad failed: err %d", err);
        return err;
    }

    err = ble_gap_adv_set_data(buf, buf_len);
    if (err != 0) {
        BT_ERR("Advertising set failed: err %d", err);
        return err;
    }

    if (sd && (param->options & BLE_MESH_ADV_OPT_CONNECTABLE)) {
        buf_len = 0;

        err = set_ad(sd, sd_len, buf, &buf_len);
        if (err) {
            BT_ERR("set_ad failed: err %d", err);
            return err;
        }

        err = ble_gap_adv_rsp_set_data(buf, buf_len);
        if (err != 0) {
            BT_ERR("Scan rsp failed: err %d", err);
            return err;
        }
    }

    memset(&adv_params, 0, sizeof adv_params);
    adv_params.itvl_min = param->interval_min;
    adv_params.itvl_max = param->interval_max;

    if (param->options & BLE_MESH_ADV_OPT_CONNECTABLE) {
        adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
        adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    } else if (sd != NULL) {
        adv_params.conn_mode = BLE_GAP_CONN_MODE_NON;
        adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    } else {
        adv_params.conn_mode = BLE_GAP_CONN_MODE_NON;
        adv_params.disc_mode = BLE_GAP_DISC_MODE_NON;
    }

    err = ble_gap_adv_start(BLE_OWN_ADDR_PUBLIC, NULL, BLE_HS_FOREVER, &adv_params,
                            gap_event_cb, NULL);
    if (err) {
        BT_ERR("Advertising start failed: err %d", err);
        return err;
    }

#if BLE_MESH_DEV
    bt_mesh_atomic_set_bit(bt_mesh_dev.flags, BLE_MESH_DEV_ADVERTISING);

    if (!(param->options & BLE_MESH_ADV_OPT_ONE_TIME)) {
        bt_mesh_atomic_set_bit(bt_mesh_dev.flags, BLE_MESH_DEV_KEEP_ADVERTISING);
    }
#endif

    return 0;
}