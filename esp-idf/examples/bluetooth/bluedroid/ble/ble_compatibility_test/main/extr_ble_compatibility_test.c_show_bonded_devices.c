#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bd_addr; } ;
typedef  TYPE_1__ esp_ble_bond_dev_t ;
typedef  int /*<<< orphan*/  esp_bd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXAMPLE_DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  EXAMPLE_TAG ; 
 int /*<<< orphan*/  esp_ble_get_bond_device_list (int*,TYPE_1__*) ; 
 int esp_ble_get_bond_device_num () ; 
 int /*<<< orphan*/  esp_log_buffer_hex (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static void show_bonded_devices(void)
{
    int dev_num = esp_ble_get_bond_device_num();

    esp_ble_bond_dev_t *dev_list = (esp_ble_bond_dev_t *)malloc(sizeof(esp_ble_bond_dev_t) * dev_num);
    esp_ble_get_bond_device_list(&dev_num, dev_list);
    EXAMPLE_DEBUG(EXAMPLE_TAG, "Bonded devices number : %d\n", dev_num);

    EXAMPLE_DEBUG(EXAMPLE_TAG, "Bonded devices list : %d\n", dev_num);
    for (int i = 0; i < dev_num; i++) {
        #if DEBUG_ON
        esp_log_buffer_hex(EXAMPLE_TAG, (void *)dev_list[i].bd_addr, sizeof(esp_bd_addr_t));
        #endif
    }

    free(dev_list);
}