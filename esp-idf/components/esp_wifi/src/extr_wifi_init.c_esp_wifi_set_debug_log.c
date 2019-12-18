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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_LOG_DEBUG ; 
 int /*<<< orphan*/  WIFI_LOG_INFO ; 
 int /*<<< orphan*/  WIFI_LOG_MODULE_ALL ; 
 int /*<<< orphan*/  WIFI_LOG_MODULE_COEX ; 
 int /*<<< orphan*/  WIFI_LOG_MODULE_MESH ; 
 int /*<<< orphan*/  WIFI_LOG_MODULE_WIFI ; 
 int /*<<< orphan*/  WIFI_LOG_SUBMODULE_ALL ; 
 int /*<<< orphan*/  WIFI_LOG_SUBMODULE_CONN ; 
 int /*<<< orphan*/  WIFI_LOG_SUBMODULE_INIT ; 
 int /*<<< orphan*/  WIFI_LOG_SUBMODULE_IOCTL ; 
 int /*<<< orphan*/  WIFI_LOG_SUBMODULE_SCAN ; 
 int /*<<< orphan*/  WIFI_LOG_VERBOSE ; 
 int /*<<< orphan*/  esp_wifi_internal_set_log_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_internal_set_log_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void esp_wifi_set_debug_log(void)
{
    /* set WiFi log level and module */
#if CONFIG_ESP32_WIFI_DEBUG_LOG_ENABLE
    uint32_t g_wifi_log_level = WIFI_LOG_INFO;
    uint32_t g_wifi_log_module = 0;
    uint32_t g_wifi_log_submodule = 0;
#if CONFIG_ESP32_WIFI_DEBUG_LOG_DEBUG
    g_wifi_log_level = WIFI_LOG_DEBUG;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_VERBOSE
    g_wifi_log_level = WIFI_LOG_VERBOSE;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_MODULE_ALL
    g_wifi_log_module = WIFI_LOG_MODULE_ALL;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_MODULE_WIFI
    g_wifi_log_module = WIFI_LOG_MODULE_WIFI;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_MODULE_COEX
    g_wifi_log_module = WIFI_LOG_MODULE_COEX;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_MODULE_MESH
    g_wifi_log_module = WIFI_LOG_MODULE_MESH;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_SUBMODULE_ALL
    g_wifi_log_submodule |= WIFI_LOG_SUBMODULE_ALL;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_SUBMODULE_INIT
    g_wifi_log_submodule |= WIFI_LOG_SUBMODULE_INIT;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_SUBMODULE_IOCTL
    g_wifi_log_submodule |= WIFI_LOG_SUBMODULE_IOCTL;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_SUBMODULE_CONN
    g_wifi_log_submodule |= WIFI_LOG_SUBMODULE_CONN;
#endif
#if CONFIG_ESP32_WIFI_DEBUG_LOG_SUBMODULE_SCAN
    g_wifi_log_submodule |= WIFI_LOG_SUBMODULE_SCAN;
#endif
    esp_wifi_internal_set_log_level(g_wifi_log_level);
    esp_wifi_internal_set_log_mod(g_wifi_log_module, g_wifi_log_submodule, true);

#endif /* CONFIG_ESP32_WIFI_DEBUG_LOG_ENABLE*/

}