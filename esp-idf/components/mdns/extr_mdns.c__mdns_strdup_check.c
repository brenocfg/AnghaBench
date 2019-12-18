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
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 char* strdup (char*) ; 

__attribute__((used)) static esp_err_t _mdns_strdup_check(char ** out, char * in)
{
    if (in && in[0]) {
        *out = strdup(in);
        if (!*out) {
            return ESP_FAIL;
        }
        return ESP_OK;
    }
    *out = NULL;
    return ESP_OK;
}