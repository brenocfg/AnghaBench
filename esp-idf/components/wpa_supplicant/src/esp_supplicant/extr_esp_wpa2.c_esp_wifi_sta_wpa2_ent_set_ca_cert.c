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
 int /*<<< orphan*/  ESP_OK ; 
 unsigned char const* g_wpa_ca_cert ; 
 int g_wpa_ca_cert_len ; 

esp_err_t esp_wifi_sta_wpa2_ent_set_ca_cert(const unsigned char *ca_cert, int ca_cert_len)
{
    if (ca_cert && ca_cert_len > 0) {
        g_wpa_ca_cert = ca_cert;
        g_wpa_ca_cert_len = ca_cert_len;
    }

    return ESP_OK;
}