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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;

/* Variables and functions */
 int /*<<< orphan*/ * btc_ble_mesh_model_find_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint16_t *esp_ble_mesh_is_model_subscribed_to_group(esp_ble_mesh_model_t *model, uint16_t group_addr)
{
    if (model == NULL) {
        return NULL;
    }
    return btc_ble_mesh_model_find_group(model, group_addr);
}