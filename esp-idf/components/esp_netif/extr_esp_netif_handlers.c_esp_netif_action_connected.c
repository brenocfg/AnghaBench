#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* esp_netif; int if_index; int ip_changed; int /*<<< orphan*/  ip_info; } ;
typedef  TYPE_1__ ip_event_got_ip_t ;
typedef  int /*<<< orphan*/  ip ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  evt ;
typedef  int /*<<< orphan*/  esp_netif_ip_info_t ;
typedef  scalar_t__ esp_netif_dhcp_status_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_NETIF_CALL_CHECK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_NETIF_DHCP_INIT ; 
 scalar_t__ ESP_NETIF_DHCP_STOPPED ; 
 int /*<<< orphan*/  ESP_NETIF_IP_EVENT_GOT_IP ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  IP_EVENT ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_event_send_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_netif_dhcpc_get_status (void*,scalar_t__*) ; 
 int /*<<< orphan*/  esp_netif_dhcpc_start (void*) ; 
 int /*<<< orphan*/  esp_netif_get_event_id (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_netif_get_ip_info (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_get_old_ip_info (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_netif_is_valid_static_ip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_set_old_ip_info (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_up (void*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void esp_netif_action_connected(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data)
{
    esp_netif_dhcp_status_t status;

    ESP_LOGD(TAG, "esp_netif action connected with netif%p from event_id=%d", esp_netif, event_id);
    esp_netif_up(esp_netif);

    esp_netif_dhcpc_get_status(esp_netif, &status);
    if (status == ESP_NETIF_DHCP_INIT) {
        esp_netif_dhcpc_start(esp_netif);
    } else if (status == ESP_NETIF_DHCP_STOPPED) {
        //
        esp_netif_ip_info_t ip;
        esp_netif_ip_info_t old_ip;

        esp_netif_get_ip_info(esp_netif, &ip);
        esp_netif_get_old_ip_info(esp_netif, &old_ip);

        if (esp_netif_is_valid_static_ip(&ip)) {
            ip_event_got_ip_t evt = {
                    .esp_netif = esp_netif,
                    .if_index = -1, // to indicate ptr to if used
                    .ip_changed = false,
            };

            if (memcmp(&ip, &old_ip, sizeof(ip))) {
                evt.ip_changed = true;
            }

            memcpy(&evt.ip_info, &ip, sizeof(esp_netif_ip_info_t));
            esp_netif_set_old_ip_info(esp_netif, &ip);

            ESP_NETIF_CALL_CHECK("esp_event_send_internal in esp_netif_action_connected",
                    esp_event_send_internal(IP_EVENT, esp_netif_get_event_id(esp_netif, ESP_NETIF_IP_EVENT_GOT_IP) ,
                                                    &evt, sizeof(evt), 0), ESP_OK);
            ESP_LOGD(TAG, "static ip: ip changed=%d", evt.ip_changed);
        } else {
            ESP_LOGE(TAG, "invalid static ip");
        }
    }
}