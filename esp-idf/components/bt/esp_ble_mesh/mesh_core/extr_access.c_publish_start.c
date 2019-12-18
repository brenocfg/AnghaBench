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
typedef  int /*<<< orphan*/  u16_t ;
struct bt_mesh_model_pub {scalar_t__ count; int /*<<< orphan*/  period_start; int /*<<< orphan*/  retransmit; } ;
struct bt_mesh_model {struct bt_mesh_model_pub* pub; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_PUB_TRANSMIT_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int /*<<< orphan*/  k_uptime_get_32 () ; 

__attribute__((used)) static void publish_start(u16_t duration, int err, void *user_data)
{
    struct bt_mesh_model *mod = user_data;
    struct bt_mesh_model_pub *pub = mod->pub;

    if (err) {
        BT_ERR("Failed to publish: err %d", err);
        return;
    }

    /* Initialize the timestamp for the beginning of a new period */
    if (pub->count == BLE_MESH_PUB_TRANSMIT_COUNT(pub->retransmit)) {
        pub->period_start = k_uptime_get_32();
    }
}