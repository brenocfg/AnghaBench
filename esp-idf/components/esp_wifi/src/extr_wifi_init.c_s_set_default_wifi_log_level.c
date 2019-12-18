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
 int /*<<< orphan*/  CONFIG_LOG_DEFAULT_LEVEL ; 
 int /*<<< orphan*/  esp_log_level_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __attribute__((constructor)) s_set_default_wifi_log_level(void)
{
    /* WiFi libraries aren't compiled to know CONFIG_LOG_DEFAULT_LEVEL,
       so set it at runtime startup. Done here not in esp_wifi_init() to allow
       the user to set the level again before esp_wifi_init() is called.
    */
    esp_log_level_set("wifi", CONFIG_LOG_DEFAULT_LEVEL);
    esp_log_level_set("mesh", CONFIG_LOG_DEFAULT_LEVEL);
}