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
struct bt_mesh_cfg_srv {int relay; int beacon; scalar_t__ default_ttl; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_TTL_MAX ; 

__attribute__((used)) static bool conf_is_valid(struct bt_mesh_cfg_srv *cfg)
{
    if (cfg->relay > 0x02) {
        return false;
    }

    if (cfg->beacon > 0x01) {
        return false;
    }

    if (cfg->default_ttl > BLE_MESH_TTL_MAX) {
        return false;
    }

    return true;
}