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
struct addrinfo {int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  ESP_ERR_ESP_TLS_CANNOT_RESOLVE_HOSTNAME ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char*,unsigned long) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 char* strndup (char const*,size_t) ; 

__attribute__((used)) static esp_err_t resolve_host_name(const char *host, size_t hostlen, struct addrinfo **address_info)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    char *use_host = strndup(host, hostlen);
    if (!use_host) {
        return ESP_ERR_NO_MEM;
    }

    ESP_LOGD(TAG, "host:%s: strlen %lu", use_host, (unsigned long)hostlen);
    if (getaddrinfo(use_host, NULL, &hints, address_info)) {
        ESP_LOGE(TAG, "couldn't get hostname for :%s:", use_host);
        free(use_host);
        return ESP_ERR_ESP_TLS_CANNOT_RESOLVE_HOSTNAME;
    }
    free(use_host);
    return ESP_OK;
}