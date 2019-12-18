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
typedef  int /*<<< orphan*/  nvs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_NAMESPACE ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  NVS_READWRITE ; 
 scalar_t__ VALID_NETIF_ID (void*) ; 
 int /*<<< orphan*/  esp_netif_get_ifkey (void*) ; 
 int /*<<< orphan*/  nvs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvs_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvs_erase_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dhcp_ip_addr_erase(void *esp_netif)
{
    nvs_handle_t nvs;

    if(VALID_NETIF_ID(esp_netif)) {
        if (nvs_open(DHCP_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
            nvs_erase_key(nvs, esp_netif_get_ifkey(esp_netif));
            nvs_commit(nvs);
            nvs_close(nvs);
        }
    }
}