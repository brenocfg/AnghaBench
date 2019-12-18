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
struct bt_mesh_adv_param {int options; int interval_min; int interval_max; } ;
struct TYPE_2__ {scalar_t__ hci_version; } ;

/* Variables and functions */
 int BLE_MESH_ADV_OPT_CONNECTABLE ; 
 scalar_t__ BLE_MESH_HCI_VERSION_5_0 ; 
 TYPE_1__ bt_mesh_dev ; 

__attribute__((used)) static bool valid_adv_param(const struct bt_mesh_adv_param *param)
{
    if (!(param->options & BLE_MESH_ADV_OPT_CONNECTABLE)) {
#if BLE_MESH_DEV
        if (bt_mesh_dev.hci_version < BLE_MESH_HCI_VERSION_5_0 &&
                param->interval_min < 0x00a0) {
            return false;
        }
#endif
    }

    if (param->interval_min > param->interval_max ||
            param->interval_min < 0x0020 || param->interval_max > 0x4000) {
        return false;
    }

    return true;
}