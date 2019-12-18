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
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_BLE_READ_LOCAL_SPT_FEAT ; 
 int /*<<< orphan*/ * make_command_no_params (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BT_HDR *make_ble_read_local_supported_features(void)
{
    return make_command_no_params(HCI_BLE_READ_LOCAL_SPT_FEAT);
}