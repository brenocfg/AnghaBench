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
typedef  int /*<<< orphan*/  system_event_id_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
#define  IP_EVENT_AP_STAIPASSIGNED 132 
#define  IP_EVENT_ETH_GOT_IP 131 
#define  IP_EVENT_GOT_IP6 130 
#define  IP_EVENT_STA_GOT_IP 129 
#define  IP_EVENT_STA_LOST_IP 128 
 int /*<<< orphan*/  SYSTEM_EVENT_AP_STAIPASSIGNED ; 
 int /*<<< orphan*/  SYSTEM_EVENT_ETH_GOT_IP ; 
 int /*<<< orphan*/  SYSTEM_EVENT_GOT_IP6 ; 
 int /*<<< orphan*/  SYSTEM_EVENT_MAX ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_GOT_IP ; 
 int /*<<< orphan*/  SYSTEM_EVENT_STA_LOST_IP ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static system_event_id_t esp_event_legacy_ip_event_id(int32_t event_id)
{
    switch (event_id) {
    case IP_EVENT_STA_GOT_IP:
        return SYSTEM_EVENT_STA_GOT_IP;

    case IP_EVENT_STA_LOST_IP:
        return SYSTEM_EVENT_STA_LOST_IP;

    case IP_EVENT_AP_STAIPASSIGNED:
        return SYSTEM_EVENT_AP_STAIPASSIGNED;

    case IP_EVENT_GOT_IP6:
        return SYSTEM_EVENT_GOT_IP6;

    case IP_EVENT_ETH_GOT_IP:
        return SYSTEM_EVENT_ETH_GOT_IP;

    default:
        ESP_LOGE(TAG, "invalid ip event id %d", event_id);
        return SYSTEM_EVENT_MAX;
    }
}