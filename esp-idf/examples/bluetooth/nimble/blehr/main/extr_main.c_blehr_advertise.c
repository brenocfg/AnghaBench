#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ble_hs_adv_fields {int flags; int tx_pwr_lvl_is_present; int name_is_complete; int /*<<< orphan*/  disc_mode; int /*<<< orphan*/  conn_mode; int /*<<< orphan*/  name_len; int /*<<< orphan*/ * name; int /*<<< orphan*/  tx_pwr_lvl; } ;
struct ble_gap_adv_params {int flags; int tx_pwr_lvl_is_present; int name_is_complete; int /*<<< orphan*/  disc_mode; int /*<<< orphan*/  conn_mode; int /*<<< orphan*/  name_len; int /*<<< orphan*/ * name; int /*<<< orphan*/  tx_pwr_lvl; } ;
typedef  int /*<<< orphan*/  fields ;
typedef  int /*<<< orphan*/  adv_params ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_GAP_CONN_MODE_UND ; 
 int /*<<< orphan*/  BLE_GAP_DISC_MODE_GEN ; 
 int BLE_HS_ADV_F_BREDR_UNSUP ; 
 int BLE_HS_ADV_F_DISC_GEN ; 
 int /*<<< orphan*/  BLE_HS_ADV_TX_PWR_LVL_AUTO ; 
 int /*<<< orphan*/  BLE_HS_FOREVER ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MODLOG_DFLT (int /*<<< orphan*/ ,char*,int) ; 
 int ble_gap_adv_set_fields (struct ble_hs_adv_fields*) ; 
 int ble_gap_adv_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ble_hs_adv_fields*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blehr_addr_type ; 
 int /*<<< orphan*/  blehr_gap_event ; 
 scalar_t__ device_name ; 
 int /*<<< orphan*/  memset (struct ble_hs_adv_fields*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static void
blehr_advertise(void)
{
    struct ble_gap_adv_params adv_params;
    struct ble_hs_adv_fields fields;
    int rc;

    /*
     *  Set the advertisement data included in our advertisements:
     *     o Flags (indicates advertisement type and other general info)
     *     o Advertising tx power
     *     o Device name
     */
    memset(&fields, 0, sizeof(fields));

    /*
     * Advertise two flags:
     *      o Discoverability in forthcoming advertisement (general)
     *      o BLE-only (BR/EDR unsupported)
     */
    fields.flags = BLE_HS_ADV_F_DISC_GEN |
                   BLE_HS_ADV_F_BREDR_UNSUP;

    /*
     * Indicate that the TX power level field should be included; have the
     * stack fill this value automatically.  This is done by assigning the
     * special value BLE_HS_ADV_TX_PWR_LVL_AUTO.
     */
    fields.tx_pwr_lvl_is_present = 1;
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;

    fields.name = (uint8_t *)device_name;
    fields.name_len = strlen(device_name);
    fields.name_is_complete = 1;

    rc = ble_gap_adv_set_fields(&fields);
    if (rc != 0) {
        MODLOG_DFLT(ERROR, "error setting advertisement data; rc=%d\n", rc);
        return;
    }

    /* Begin advertising */
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    rc = ble_gap_adv_start(blehr_addr_type, NULL, BLE_HS_FOREVER,
                           &adv_params, blehr_gap_event, NULL);
    if (rc != 0) {
        MODLOG_DFLT(ERROR, "error enabling advertisement; rc=%d\n", rc);
        return;
    }
}