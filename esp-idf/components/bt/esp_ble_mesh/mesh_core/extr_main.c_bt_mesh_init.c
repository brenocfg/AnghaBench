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
typedef  int u32_t ;
struct bt_mesh_prov {int dummy; } ;
struct bt_mesh_gatt_service {int dummy; } ;
struct bt_mesh_comp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_BLE_MESH_GATT_PROXY_SERVER ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_PB_GATT ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_PROV ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_PROXY ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_adapt_init () ; 
 int /*<<< orphan*/  bt_mesh_adv_init () ; 
 int /*<<< orphan*/  bt_mesh_beacon_init () ; 
 int bt_mesh_comp_register (struct bt_mesh_comp const*) ; 
 int /*<<< orphan*/  bt_mesh_gatt_init () ; 
 int /*<<< orphan*/  bt_mesh_gatts_service_register (struct bt_mesh_gatt_service*) ; 
 int /*<<< orphan*/  bt_mesh_hci_init () ; 
 int /*<<< orphan*/  bt_mesh_k_init () ; 
 int /*<<< orphan*/  bt_mesh_net_init () ; 
 int bt_mesh_prov_init (struct bt_mesh_prov const*) ; 
 int /*<<< orphan*/  bt_mesh_proxy_init () ; 
 int /*<<< orphan*/  bt_mesh_proxy_prov_client_init () ; 
 int /*<<< orphan*/  bt_mesh_rand (int*,int) ; 
 int /*<<< orphan*/  bt_mesh_settings_init () ; 
 int /*<<< orphan*/  bt_mesh_trans_init () ; 
 int portTICK_PERIOD_MS ; 
 int provisioner_prov_init (struct bt_mesh_prov const*) ; 
 int provisioner_upper_init () ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

int bt_mesh_init(const struct bt_mesh_prov *prov,
                 const struct bt_mesh_comp *comp)
{
    int err;

    bt_mesh_k_init();

    bt_mesh_hci_init();

    bt_mesh_adapt_init();

    err = bt_mesh_comp_register(comp);
    if (err) {
        return err;
    }

    bt_mesh_gatt_init();

#if CONFIG_BLE_MESH_NODE
    extern struct bt_mesh_gatt_service proxy_svc;
    if (IS_ENABLED(CONFIG_BLE_MESH_GATT_PROXY_SERVER)) {
        bt_mesh_gatts_service_register(&proxy_svc);
    }

    extern struct bt_mesh_gatt_service prov_svc;
    if (IS_ENABLED(CONFIG_BLE_MESH_PB_GATT)) {
        bt_mesh_gatts_service_register(&prov_svc);
    }
#endif

    if (IS_ENABLED(CONFIG_BLE_MESH_PROV)) {
#if CONFIG_BLE_MESH_NODE
        err = bt_mesh_prov_init(prov);
        if (err) {
            return err;
        }
#endif
#if CONFIG_BLE_MESH_PROVISIONER
        err = provisioner_prov_init(prov);
        if (err) {
            return err;
        }
#endif
    }

    bt_mesh_net_init();
    bt_mesh_trans_init();

#if CONFIG_BLE_MESH_NODE
    /* Changed by Espressif, add random delay (0 ~ 3s) */
#if defined(CONFIG_BLE_MESH_FAST_PROV)
    u32_t delay = 0;
    bt_mesh_rand(&delay, sizeof(u32_t));
    vTaskDelay((delay % 3000) / portTICK_PERIOD_MS);
#endif
    bt_mesh_beacon_init();
#endif

    bt_mesh_adv_init();

    if (IS_ENABLED(CONFIG_BLE_MESH_PROXY)) {
#if CONFIG_BLE_MESH_NODE
        bt_mesh_proxy_init();
#endif
#if (CONFIG_BLE_MESH_PROVISIONER && CONFIG_BLE_MESH_PB_GATT) || \
    CONFIG_BLE_MESH_GATT_PROXY_CLIENT
        bt_mesh_proxy_prov_client_init();
#endif
    }

#if !CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PROVISIONER
    /* If node & provisioner are both enabled and the
     * device starts as a node, it must finish provisioning */
    err = provisioner_upper_init();
    if (err) {
        return err;
    }
#endif

#if defined(CONFIG_BLE_MESH_SETTINGS)
    if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS)) {
        bt_mesh_settings_init();
    }
#endif

    return 0;
}