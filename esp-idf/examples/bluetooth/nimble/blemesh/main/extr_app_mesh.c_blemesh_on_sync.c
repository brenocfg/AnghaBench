#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ ble_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SETTINGS ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ble_hs_id_gen_rnd (int,TYPE_1__*) ; 
 int ble_hs_id_set_rnd (int /*<<< orphan*/ ) ; 
 int bt_mesh_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  prov ; 
 int /*<<< orphan*/  settings_load () ; 
 int /*<<< orphan*/  tag ; 

__attribute__((used)) static void
blemesh_on_sync(void)
{
    int err;
    ble_addr_t addr;

    ESP_LOGI(tag, "Bluetooth initialized\n");

    /* Use NRPA */
    err = ble_hs_id_gen_rnd(1, &addr);
    assert(err == 0);
    err = ble_hs_id_set_rnd(addr.val);
    assert(err == 0);

    err = bt_mesh_init(addr.type, &prov, &comp);
    if (err) {
        ESP_LOGI(tag, "Initializing mesh failed (err %d)\n", err);
        return;
    }

    ESP_LOGI(tag, "Mesh initialized\n");

    if (IS_ENABLED(CONFIG_SETTINGS)) {
        settings_load();
    }

    if (bt_mesh_is_provisioned()) {
        ESP_LOGI(tag, "Mesh network restored from flash\n");
    }
}