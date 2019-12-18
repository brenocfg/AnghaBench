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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;

/* Variables and functions */
 int /*<<< orphan*/  btc_ble_mesh_model_pub_period_get (int /*<<< orphan*/ *) ; 

int32_t esp_ble_mesh_get_model_publish_period(esp_ble_mesh_model_t *model)
{
    if (model == NULL) {
        return 0;
    }
    return btc_ble_mesh_model_pub_period_get(model);
}