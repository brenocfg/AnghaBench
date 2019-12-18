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

/* Variables and functions */
 int /*<<< orphan*/ * g_wpa_ca_cert ; 
 scalar_t__ g_wpa_ca_cert_len ; 

void esp_wifi_sta_wpa2_ent_clear_ca_cert(void)
{
    g_wpa_ca_cert = NULL;
    g_wpa_ca_cert_len = 0;
}