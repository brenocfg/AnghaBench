#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int msg; TYPE_5__* resp_apply_config; TYPE_5__* resp_set_config; TYPE_5__* resp_get_status; } ;
typedef  TYPE_3__ WiFiConfigPayload ;
struct TYPE_7__ {TYPE_5__* data; } ;
struct TYPE_6__ {TYPE_5__* data; } ;
struct TYPE_9__ {struct TYPE_9__* connected; TYPE_2__ ssid; TYPE_1__ bssid; struct TYPE_9__* ip4_addr; int /*<<< orphan*/  sta_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
#define  WIFI_STATION_STATE__Connected 133 
#define  WIFI_STATION_STATE__Connecting 132 
#define  WIFI_STATION_STATE__ConnectionFailed 131 
#define  WI_FI_CONFIG_MSG_TYPE__TypeRespApplyConfig 130 
#define  WI_FI_CONFIG_MSG_TYPE__TypeRespGetStatus 129 
#define  WI_FI_CONFIG_MSG_TYPE__TypeRespSetConfig 128 
 int /*<<< orphan*/  free (TYPE_5__*) ; 

__attribute__((used)) static void wifi_prov_config_command_cleanup(WiFiConfigPayload *resp, void *priv_data)
{
    if (!resp) {
        return;
    }

    switch (resp->msg) {
        case WI_FI_CONFIG_MSG_TYPE__TypeRespGetStatus:
            {
                switch (resp->resp_get_status->sta_state) {
                    case WIFI_STATION_STATE__Connecting:
                        break;
                    case WIFI_STATION_STATE__Connected:
                        if (resp->resp_get_status->connected) {
                            if (resp->resp_get_status->connected->ip4_addr) {
                                free(resp->resp_get_status->connected->ip4_addr);
                            }
                            if (resp->resp_get_status->connected->bssid.data) {
                                free(resp->resp_get_status->connected->bssid.data);
                            }
                            if (resp->resp_get_status->connected->ssid.data) {
                                free(resp->resp_get_status->connected->ssid.data);
                            }
                            free(resp->resp_get_status->connected);
                        }
                        break;
                    case WIFI_STATION_STATE__ConnectionFailed:
                        break;
                    default:
                        break;
                }
                free(resp->resp_get_status);
            }
            break;
        case WI_FI_CONFIG_MSG_TYPE__TypeRespSetConfig:
            {
                free(resp->resp_set_config);
            }
            break;
        case WI_FI_CONFIG_MSG_TYPE__TypeRespApplyConfig:
            {
                free(resp->resp_apply_config);
            }
            break;
        default:
            ESP_LOGE(TAG, "Unsupported response type in cleanup_handler");
            break;
    }
    return;
}