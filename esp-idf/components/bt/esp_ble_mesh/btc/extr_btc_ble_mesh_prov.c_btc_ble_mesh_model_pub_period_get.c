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
struct bt_mesh_model {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;

/* Variables and functions */
 int /*<<< orphan*/  bt_mesh_model_pub_period_get (struct bt_mesh_model*) ; 

int32_t btc_ble_mesh_model_pub_period_get(esp_ble_mesh_model_t *mod)
{
    return bt_mesh_model_pub_period_get((struct bt_mesh_model *)mod);
}