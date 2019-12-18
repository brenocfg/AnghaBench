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
 int /*<<< orphan*/ * g_wpa_new_password ; 
 scalar_t__ g_wpa_new_password_len ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

void esp_wifi_sta_wpa2_ent_clear_new_password(void)
{
    if (g_wpa_new_password) {
        os_free(g_wpa_new_password);
    }
    g_wpa_new_password = NULL;
    g_wpa_new_password_len = 0;
}