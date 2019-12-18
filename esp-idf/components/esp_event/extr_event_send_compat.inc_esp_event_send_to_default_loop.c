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
struct TYPE_4__ {int event_id; } ;
typedef  TYPE_1__ system_event_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  TickType_t ;

/* Variables and functions */
 int /*<<< orphan*/  AP_PROBEREQRECVED ; 
 int /*<<< orphan*/  AP_STACONNECTED ; 
 int /*<<< orphan*/  AP_STADISCONNECTED ; 
 int /*<<< orphan*/  AP_STAIPASSIGNED ; 
 int /*<<< orphan*/  AP_START ; 
 int /*<<< orphan*/  AP_STOP ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ETH ; 
 int /*<<< orphan*/  ETH_CONNECTED ; 
 int /*<<< orphan*/  ETH_DISCONNECTED ; 
 int /*<<< orphan*/  ETH_GOT_IP ; 
 int /*<<< orphan*/  ETH_START ; 
 int /*<<< orphan*/  ETH_STOP ; 
 int /*<<< orphan*/  GOT_IP6 ; 
 int /*<<< orphan*/  HANDLE_SYS_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HANDLE_SYS_EVENT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP ; 
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  STA_AUTHMODE_CHANGE ; 
 int /*<<< orphan*/  STA_CONNECTED ; 
 int /*<<< orphan*/  STA_DISCONNECTED ; 
 int /*<<< orphan*/  STA_GOT_IP ; 
 int /*<<< orphan*/  STA_LOST_IP ; 
 int /*<<< orphan*/  STA_START ; 
 int /*<<< orphan*/  STA_STOP ; 
 int /*<<< orphan*/  STA_WPS_ER_FAILED ; 
 int /*<<< orphan*/  STA_WPS_ER_PBC_OVERLAP ; 
 int /*<<< orphan*/  STA_WPS_ER_PIN ; 
 int /*<<< orphan*/  STA_WPS_ER_SUCCESS ; 
 int /*<<< orphan*/  STA_WPS_ER_TIMEOUT ; 
 int /*<<< orphan*/  WIFI ; 
 int /*<<< orphan*/  WIFI_READY ; 
 int /*<<< orphan*/  ap_probereqrecved ; 
 int /*<<< orphan*/  auth_change ; 
 int /*<<< orphan*/  connected ; 
 int /*<<< orphan*/  disconnected ; 
 int /*<<< orphan*/  esp_system_event_debug (TYPE_1__*) ; 
 int /*<<< orphan*/  got_ip ; 
 int /*<<< orphan*/  got_ip6 ; 
 int /*<<< orphan*/  scan_done ; 
 int /*<<< orphan*/  sta_connected ; 
 int /*<<< orphan*/  sta_disconnected ; 
 int /*<<< orphan*/  sta_er_fail_reason ; 
 int /*<<< orphan*/  sta_er_pin ; 

esp_err_t esp_event_send_to_default_loop(system_event_t *event)
{
#ifdef WITH_EVENT_DEBUG
    esp_system_event_debug(event);
#endif // WITH_EVENT_DEBUG

    const TickType_t send_timeout = 0;
    switch (event->event_id) {
        /* Wi-Fi common events */
        HANDLE_SYS_EVENT(WIFI, WIFI_READY);
        HANDLE_SYS_EVENT_ARG(WIFI, SCAN_DONE, scan_done);
        HANDLE_SYS_EVENT(WIFI, STA_START);
        HANDLE_SYS_EVENT(WIFI, STA_STOP);

        /* STA events */
        HANDLE_SYS_EVENT_ARG(WIFI, STA_CONNECTED, connected);
        HANDLE_SYS_EVENT_ARG(WIFI, STA_DISCONNECTED, disconnected);
        HANDLE_SYS_EVENT_ARG(WIFI, STA_AUTHMODE_CHANGE, auth_change);

        /* WPS events */
        HANDLE_SYS_EVENT(WIFI, STA_WPS_ER_SUCCESS);
        HANDLE_SYS_EVENT(WIFI, STA_WPS_ER_TIMEOUT);
        HANDLE_SYS_EVENT_ARG(WIFI, STA_WPS_ER_FAILED, sta_er_fail_reason);
        HANDLE_SYS_EVENT_ARG(WIFI, STA_WPS_ER_PIN, sta_er_pin);
        HANDLE_SYS_EVENT(WIFI, STA_WPS_ER_PBC_OVERLAP);

        /* AP events */
        HANDLE_SYS_EVENT(WIFI, AP_START);
        HANDLE_SYS_EVENT(WIFI, AP_STOP);
        HANDLE_SYS_EVENT_ARG(WIFI, AP_STACONNECTED, sta_connected);
        HANDLE_SYS_EVENT_ARG(WIFI, AP_STADISCONNECTED, sta_disconnected);
        HANDLE_SYS_EVENT_ARG(WIFI, AP_PROBEREQRECVED, ap_probereqrecved);
#if CONFIG_ETH_ENABLED
        /* Ethernet events */
        /* Some extra defines to fit the old naming scheme... */
#define ETH_EVENT_ETH_START ETHERNET_EVENT_START
#define ETH_EVENT_ETH_STOP ETHERNET_EVENT_STOP
#define ETH_EVENT_ETH_CONNECTED ETHERNET_EVENT_CONNECTED
#define ETH_EVENT_ETH_DISCONNECTED ETHERNET_EVENT_DISCONNECTED

        HANDLE_SYS_EVENT(ETH, ETH_START);
        HANDLE_SYS_EVENT(ETH, ETH_STOP);
        HANDLE_SYS_EVENT(ETH, ETH_CONNECTED);
        HANDLE_SYS_EVENT(ETH, ETH_DISCONNECTED);
#endif
        /* IP events */
        HANDLE_SYS_EVENT_ARG(IP, STA_GOT_IP, got_ip);
        HANDLE_SYS_EVENT_ARG(IP, ETH_GOT_IP, got_ip);
        HANDLE_SYS_EVENT(IP, STA_LOST_IP);
        HANDLE_SYS_EVENT_ARG(IP, GOT_IP6, got_ip6);
        HANDLE_SYS_EVENT(IP, AP_STAIPASSIGNED);
        default:
            return ESP_ERR_NOT_SUPPORTED;
    }
}