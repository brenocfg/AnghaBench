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
typedef  int /*<<< orphan*/  eth_duplex_t ;
typedef  int /*<<< orphan*/  esp_eth_mac_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 

__attribute__((used)) static esp_err_t emac_opencores_set_duplex(esp_eth_mac_t *mac, eth_duplex_t duplex)
{
    /* QEMU doesn't emulate full/half duplex, so accept any value */
    return ESP_OK;
}