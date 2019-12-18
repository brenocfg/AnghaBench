#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * wifi_rxcb_t ;
typedef  TYPE_2__* wifi_netif_driver_t ;
typedef  size_t wifi_interface_t ;
typedef  int /*<<< orphan*/  esp_netif_receive_t ;
typedef  void* esp_err_t ;
struct TYPE_4__ {void* netif; } ;
struct TYPE_5__ {size_t wifi_if; TYPE_1__ base; } ;

/* Variables and functions */
 void* ESP_ERR_INVALID_ARG ; 
 void* ESP_ERR_INVALID_STATE ; 
 void* ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,size_t,...) ; 
 void* ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
#define  WIFI_IF_AP 129 
#define  WIFI_IF_STA 128 
 void* esp_wifi_internal_reg_rxcb (size_t,int /*<<< orphan*/ *) ; 
 void** s_wifi_netifs ; 
 int /*<<< orphan*/ * s_wifi_rxcbs ; 
 int /*<<< orphan*/ * wifi_ap_receive ; 
 int /*<<< orphan*/ * wifi_sta_receive ; 

esp_err_t esp_wifi_register_if_rxcb(wifi_netif_driver_t ifx, esp_netif_receive_t fn, void * arg)
{
    if (ifx->base.netif != arg) {
        ESP_LOGE(TAG, "Invalid argument: supplied netif=%p does not equal to interface netif=%p", arg, ifx->base.netif);
        return ESP_ERR_INVALID_ARG;
    }
    wifi_interface_t wifi_interface = ifx->wifi_if;
    s_wifi_rxcbs[wifi_interface] = fn;
    wifi_rxcb_t rxcb = NULL;
    esp_err_t ret;

    switch (wifi_interface)
    {
    case WIFI_IF_STA:
        rxcb = wifi_sta_receive;
        break;
    
    case WIFI_IF_AP:
        rxcb = wifi_ap_receive;
        break;

    default:
        break;
    }

    if (rxcb == NULL) {
        ESP_LOGE(TAG, "Unknown wifi interface id if=%d", wifi_interface);
        return ESP_ERR_NOT_SUPPORTED;
    }

    if ((ret = esp_wifi_internal_reg_rxcb(wifi_interface,  rxcb)) != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_internal_reg_rxcb for if=%d failed with %d", wifi_interface, ret);
        return ESP_ERR_INVALID_STATE;
    }

    s_wifi_netifs[wifi_interface] = ifx->base.netif;
    return ESP_OK;
}