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
typedef  int /*<<< orphan*/  tBTA_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmUpdateDuplicateExceptionalList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_ble_update_duplicate_exceptional_list(uint8_t subcode, uint32_t info_type, BD_ADDR device_info,
                                 tBTA_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK p_update_duplicate_ignore_list_cback)
{
    BTA_DmUpdateDuplicateExceptionalList(subcode, info_type, device_info, p_update_duplicate_ignore_list_cback);
}