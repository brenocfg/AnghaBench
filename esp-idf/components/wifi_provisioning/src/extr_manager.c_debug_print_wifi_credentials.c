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
struct TYPE_3__ {scalar_t__ password; scalar_t__ ssid; } ;
typedef  TYPE_1__ wifi_sta_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  memset (scalar_t__,char,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strnlen (char const*,int) ; 

__attribute__((used)) static void debug_print_wifi_credentials(wifi_sta_config_t sta, const char* pretext)
{
    size_t passlen = strlen((const char*) sta.password);
    ESP_LOGD(TAG, "%s Wi-Fi SSID     : %.*s", pretext,
             strnlen((const char *) sta.ssid, sizeof(sta.ssid)), (const char *) sta.ssid);

    if (passlen) {
        /* Mask password partially if longer than 3, else mask it completely */
        memset(sta.password + (passlen > 3), '*', passlen - 2*(passlen > 3));
        ESP_LOGD(TAG, "%s Wi-Fi Password : %s", pretext, (const char *) sta.password);
    }
}