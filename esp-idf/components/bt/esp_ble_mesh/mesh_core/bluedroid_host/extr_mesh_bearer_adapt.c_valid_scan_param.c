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
struct bt_mesh_scan_param {scalar_t__ type; scalar_t__ filter_dup; int interval; int window; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_SCAN_ACTIVE ; 
 scalar_t__ BLE_MESH_SCAN_FILTER_DUP_DISABLE ; 
 scalar_t__ BLE_MESH_SCAN_FILTER_DUP_ENABLE ; 
 scalar_t__ BLE_MESH_SCAN_PASSIVE ; 

__attribute__((used)) static bool valid_scan_param(const struct bt_mesh_scan_param *param)
{
    if (param->type != BLE_MESH_SCAN_PASSIVE &&
            param->type != BLE_MESH_SCAN_ACTIVE) {
        return false;
    }

    if (param->filter_dup != BLE_MESH_SCAN_FILTER_DUP_DISABLE &&
            param->filter_dup != BLE_MESH_SCAN_FILTER_DUP_ENABLE) {
        return false;
    }

    if (param->interval < 0x0004 || param->interval > 0x4000) {
        return false;
    }

    if (param->window < 0x0004 || param->window > 0x4000) {
        return false;
    }

    if (param->window > param->interval) {
        return false;
    }

    return true;
}