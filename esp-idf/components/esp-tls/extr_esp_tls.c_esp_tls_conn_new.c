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
typedef  int /*<<< orphan*/  esp_tls_t ;
typedef  int /*<<< orphan*/  esp_tls_cfg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  esp_tls_conn_delete (int /*<<< orphan*/ *) ; 
 int esp_tls_low_level_conn (char const*,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

esp_tls_t *esp_tls_conn_new(const char *hostname, int hostlen, int port, const esp_tls_cfg_t *cfg)
{
    esp_tls_t *tls = (esp_tls_t *)calloc(1, sizeof(esp_tls_t));
    if (!tls) {
        return NULL;
    }
    /* esp_tls_conn_new() API establishes connection in a blocking manner thus this loop ensures that esp_tls_conn_new()
       API returns only after connection is established unless there is an error*/
    while (1) {
        int ret = esp_tls_low_level_conn(hostname, hostlen, port, cfg, tls);
        if (ret == 1) {
            return tls;
        } else if (ret == -1) {
            esp_tls_conn_delete(tls);
            ESP_LOGE(TAG, "Failed to open new connection");
            return NULL;
        }
    }
    return NULL;
}