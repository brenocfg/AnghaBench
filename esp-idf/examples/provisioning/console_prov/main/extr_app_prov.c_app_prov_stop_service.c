#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EVENT_ANY_ID ; 
 int /*<<< orphan*/  IP_EVENT ; 
 int /*<<< orphan*/  IP_EVENT_STA_GOT_IP ; 
 int /*<<< orphan*/  WIFI_EVENT ; 
 int /*<<< orphan*/  app_prov_event_handler ; 
 int /*<<< orphan*/  esp_event_handler_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_prov ; 
 int /*<<< orphan*/  protocomm_console_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocomm_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocomm_remove_endpoint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  protocomm_unset_security (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  protocomm_unset_version (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void app_prov_stop_service(void)
{
    /* Remove provisioning endpoint */
    protocomm_remove_endpoint(g_prov->pc, "prov-config");
    /* Unset provisioning security */
    protocomm_unset_security(g_prov->pc, "prov-session");
    /* Unset provisioning version endpoint */
    protocomm_unset_version(g_prov->pc, "proto-ver");
    /* Stop protocomm console service */
    protocomm_console_stop(g_prov->pc);
    /* Delete protocomm instance */
    protocomm_delete(g_prov->pc);

    /* Remove event handler */
    esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, app_prov_event_handler);
    esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, app_prov_event_handler);
}