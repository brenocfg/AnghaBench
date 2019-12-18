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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  ETHERNET_EVENT_CONNECTED ; 
 int /*<<< orphan*/  ETHERNET_EVENT_DISCONNECTED ; 
 int /*<<< orphan*/  ETHERNET_EVENT_START ; 
 int /*<<< orphan*/  ETHERNET_EVENT_STOP ; 
 int /*<<< orphan*/  ETH_CHECK (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_EVENT ; 
 int /*<<< orphan*/  IP_EVENT ; 
 int /*<<< orphan*/  IP_EVENT_ETH_GOT_IP ; 
 int /*<<< orphan*/  esp_event_handler_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_netif_action_connected ; 
 int /*<<< orphan*/  esp_netif_action_disconnected ; 
 int /*<<< orphan*/  esp_netif_action_got_ip ; 
 int /*<<< orphan*/  esp_netif_action_start ; 
 int /*<<< orphan*/  esp_netif_action_stop ; 
 int /*<<< orphan*/  fail ; 

esp_err_t esp_eth_clear_default_handlers(void* esp_netif)
{
    esp_err_t ret;
    ETH_CHECK(esp_netif, "esp-netif handle can't be null", fail, ESP_ERR_INVALID_ARG);

    esp_event_handler_unregister(ETH_EVENT, ETHERNET_EVENT_START, esp_netif_action_start);
    esp_event_handler_unregister(ETH_EVENT, ETHERNET_EVENT_STOP, esp_netif_action_stop);
    esp_event_handler_unregister(ETH_EVENT, ETHERNET_EVENT_CONNECTED, esp_netif_action_connected);
    esp_event_handler_unregister(ETH_EVENT, ETHERNET_EVENT_DISCONNECTED, esp_netif_action_disconnected);
    esp_event_handler_unregister(IP_EVENT, IP_EVENT_ETH_GOT_IP, esp_netif_action_got_ip);
    return ESP_OK;
fail:
    return ret;
}