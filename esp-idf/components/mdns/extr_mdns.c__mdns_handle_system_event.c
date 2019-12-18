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
typedef  size_t mdns_if_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  esp_netif_t ;
typedef  int /*<<< orphan*/  esp_netif_dhcp_status_t ;
typedef  scalar_t__ esp_event_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_NETIF_DHCP_STOPPED ; 
#define  ETHERNET_EVENT_CONNECTED 136 
#define  ETHERNET_EVENT_DISCONNECTED 135 
 int ETHERNET_EVENT_START ; 
 scalar_t__ ETH_EVENT ; 
 scalar_t__ IP_EVENT ; 
#define  IP_EVENT_ETH_GOT_IP 134 
#define  IP_EVENT_GOT_IP6 133 
#define  IP_EVENT_STA_GOT_IP 132 
 size_t MDNS_IF_AP ; 
 size_t MDNS_IF_ETH ; 
 size_t MDNS_IF_STA ; 
 int /*<<< orphan*/  MDNS_IP_PROTOCOL_V4 ; 
 int /*<<< orphan*/  MDNS_IP_PROTOCOL_V6 ; 
 scalar_t__ WIFI_EVENT ; 
#define  WIFI_EVENT_AP_START 131 
#define  WIFI_EVENT_AP_STOP 130 
#define  WIFI_EVENT_STA_CONNECTED 129 
#define  WIFI_EVENT_STA_DISCONNECTED 128 
 int WIFI_EVENT_STA_START ; 
 int /*<<< orphan*/  _mdns_announce_pcb (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mdns_disable_pcb (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mdns_enable_pcb (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mdns_get_esp_netif (size_t) ; 
 size_t _mdns_get_if_from_esp_netif (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mdns_server ; 
 int /*<<< orphan*/  esp_netif_dhcpc_get_status (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_get_handle_from_ifkey (char*) ; 
 int /*<<< orphan*/ * s_esp_netifs ; 

__attribute__((used)) static void _mdns_handle_system_event(esp_event_base_t event_base,
                                      int32_t event_id, esp_netif_t* interface)
{
    if (!_mdns_server) {
        return;
    }

    // Initialize handles to esp-netif if appropriate mdns supported interface started
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        s_esp_netifs[MDNS_IF_STA] = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_START) {
        s_esp_netifs[MDNS_IF_AP] = esp_netif_get_handle_from_ifkey("WIFI_AP_DEF");
#if CONFIG_ETH_ENABLED
    } else if (event_base == ETH_EVENT && event_id == ETHERNET_EVENT_START) {
        s_esp_netifs[MDNS_IF_ETH] = esp_netif_get_handle_from_ifkey("ETH_DEF");
#endif
    }

    esp_netif_dhcp_status_t dcst;
    if (event_base == WIFI_EVENT) {
        switch(event_id) {
            case WIFI_EVENT_STA_CONNECTED:
                if (!esp_netif_dhcpc_get_status(_mdns_get_esp_netif(MDNS_IF_STA), &dcst)) {
                    if (dcst == ESP_NETIF_DHCP_STOPPED) {
                        _mdns_enable_pcb(MDNS_IF_STA, MDNS_IP_PROTOCOL_V4);
                    }
                }
                break;
            case WIFI_EVENT_STA_DISCONNECTED:
                _mdns_disable_pcb(MDNS_IF_STA, MDNS_IP_PROTOCOL_V4);
                _mdns_disable_pcb(MDNS_IF_STA, MDNS_IP_PROTOCOL_V6);
                break;
            case WIFI_EVENT_AP_START:
                _mdns_enable_pcb(MDNS_IF_AP, MDNS_IP_PROTOCOL_V4);
                break;
            case WIFI_EVENT_AP_STOP:
                _mdns_disable_pcb(MDNS_IF_AP, MDNS_IP_PROTOCOL_V4);
                _mdns_disable_pcb(MDNS_IF_AP, MDNS_IP_PROTOCOL_V6);
                break;
            default:
                break;
        }
    }
#if CONFIG_ETH_ENABLED
    else if (event_base == ETH_EVENT) {
        switch (event_id) {
            case ETHERNET_EVENT_CONNECTED:
                if (!esp_netif_dhcpc_get_status(_mdns_get_esp_netif(MDNS_IF_ETH), &dcst)) {
                    if (dcst == ESP_NETIF_DHCP_STOPPED) {
                        _mdns_enable_pcb(MDNS_IF_ETH, MDNS_IP_PROTOCOL_V4);
                    }
                }
                break;
            case ETHERNET_EVENT_DISCONNECTED:
                _mdns_disable_pcb(MDNS_IF_ETH, MDNS_IP_PROTOCOL_V4);
                _mdns_disable_pcb(MDNS_IF_ETH, MDNS_IP_PROTOCOL_V6);
                break;
            default:
                break;
        }
    }
#endif
    else if (event_base == IP_EVENT) {
        switch (event_id) {
            case IP_EVENT_STA_GOT_IP:
                _mdns_enable_pcb(MDNS_IF_STA, MDNS_IP_PROTOCOL_V4);
                _mdns_announce_pcb(MDNS_IF_STA, MDNS_IP_PROTOCOL_V6, NULL, 0, true);
                break;
#if CONFIG_ETH_ENABLED
            case IP_EVENT_ETH_GOT_IP:
                _mdns_enable_pcb(MDNS_IF_ETH, MDNS_IP_PROTOCOL_V4);
                break;
#endif
            case IP_EVENT_GOT_IP6:
            {
                mdns_if_t mdns_if = _mdns_get_if_from_esp_netif(interface);
                _mdns_enable_pcb(mdns_if, MDNS_IP_PROTOCOL_V6);
                _mdns_announce_pcb(mdns_if, MDNS_IP_PROTOCOL_V4, NULL, 0, true);

            }
                break;
            default:
                break;
        }
    }
}