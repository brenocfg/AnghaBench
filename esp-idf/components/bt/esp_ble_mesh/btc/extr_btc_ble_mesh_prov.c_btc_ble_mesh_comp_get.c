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
typedef  int /*<<< orphan*/  esp_ble_mesh_comp_t ;

/* Variables and functions */
 scalar_t__ bt_mesh_comp_get () ; 

const esp_ble_mesh_comp_t *btc_ble_mesh_comp_get(void)
{
    return (const esp_ble_mesh_comp_t *)bt_mesh_comp_get();
}