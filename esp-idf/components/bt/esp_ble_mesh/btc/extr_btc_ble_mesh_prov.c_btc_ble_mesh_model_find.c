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
struct bt_mesh_elem {int dummy; } ;
typedef  int /*<<< orphan*/  esp_ble_mesh_model_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_elem_t ;

/* Variables and functions */
 scalar_t__ bt_mesh_model_find (struct bt_mesh_elem*,int /*<<< orphan*/ ) ; 

esp_ble_mesh_model_t *btc_ble_mesh_model_find(const esp_ble_mesh_elem_t *elem, uint16_t id)
{
    return (esp_ble_mesh_model_t *)bt_mesh_model_find((struct bt_mesh_elem *)elem, id);
}