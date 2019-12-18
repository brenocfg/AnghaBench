#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netif_cfg ;
typedef  int /*<<< orphan*/  esp_netif_t ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ esp_netif_inherent_config_t ;
struct TYPE_6__ {int /*<<< orphan*/  stack; TYPE_1__* base; } ;
typedef  TYPE_2__ esp_netif_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_NETIF_BASE_DEFAULT_WIFI_AP ; 
 int /*<<< orphan*/  ESP_NETIF_BASE_DEFAULT_WIFI_STA ; 
 int /*<<< orphan*/  ESP_NETIF_DHCP_CLIENT ; 
 int /*<<< orphan*/  ESP_NETIF_DHCP_SERVER ; 
 int /*<<< orphan*/  ESP_NETIF_NETSTACK_DEFAULT_WIFI_AP ; 
 int /*<<< orphan*/  ESP_NETIF_NETSTACK_DEFAULT_WIFI_STA ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_attach_wifi_ap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_attach_wifi_station (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_dhcpc_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_dhcps_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_netif_new (TYPE_2__*) ; 
 int /*<<< orphan*/  esp_wifi_set_default_wifi_ap_handlers () ; 
 int /*<<< orphan*/  esp_wifi_set_default_wifi_sta_handlers () ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

esp_err_t esp_netif_create_default_wifi_mesh_netifs(esp_netif_t **p_netif_sta, esp_netif_t **p_netif_ap)
{
    // Create "almost" default AP, with un-flagged DHCP server
    esp_netif_inherent_config_t netif_cfg;
    memcpy(&netif_cfg, ESP_NETIF_BASE_DEFAULT_WIFI_AP, sizeof(netif_cfg));
    netif_cfg.flags &= ~ESP_NETIF_DHCP_SERVER;
    esp_netif_config_t cfg_ap = {
            .base = &netif_cfg,
            .stack = ESP_NETIF_NETSTACK_DEFAULT_WIFI_AP,
    };
    esp_netif_t *netif_ap = esp_netif_new(&cfg_ap);
    assert(netif_ap);
    ESP_ERROR_CHECK(esp_netif_attach_wifi_ap(netif_ap));
    ESP_ERROR_CHECK(esp_wifi_set_default_wifi_ap_handlers());

    // ...and stop DHCP server to be compatible with former tcpip_adapter (to keep the ESP_NETIF_DHCP_STOPPED state)
    ESP_ERROR_CHECK(esp_netif_dhcps_stop(netif_ap));

    // Create "almost" default station, but with un-flagged DHCP client
    memcpy(&netif_cfg, ESP_NETIF_BASE_DEFAULT_WIFI_STA, sizeof(netif_cfg));
    netif_cfg.flags &= ~ESP_NETIF_DHCP_CLIENT;
    esp_netif_config_t cfg_sta = {
            .base = &netif_cfg,
            .stack = ESP_NETIF_NETSTACK_DEFAULT_WIFI_STA,
    };
    esp_netif_t *netif_sta = esp_netif_new(&cfg_sta);
    assert(netif_sta);
    ESP_ERROR_CHECK(esp_netif_attach_wifi_station(netif_sta));
    ESP_ERROR_CHECK(esp_wifi_set_default_wifi_sta_handlers());

    // ...and stop DHCP client (to be started separately if the station were promoted to root)
    ESP_ERROR_CHECK(esp_netif_dhcpc_stop(netif_sta));

    if (p_netif_sta) {
        *p_netif_sta = netif_sta;
    }
    if (p_netif_ap) {
        *p_netif_ap = netif_ap;
    }
    return ESP_OK;
}