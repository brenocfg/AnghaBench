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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tBTA_SET_ADV_DATA_CMPL_CBACK ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmBleSetScanRspRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_ble_set_scan_rsp_data_raw(uint8_t *raw_scan_rsp, uint32_t raw_scan_rsp_len,
                                 tBTA_SET_ADV_DATA_CMPL_CBACK p_scan_rsp_data_cback)
{
    BTA_DmBleSetScanRspRaw(raw_scan_rsp, raw_scan_rsp_len, p_scan_rsp_data_cback);
}