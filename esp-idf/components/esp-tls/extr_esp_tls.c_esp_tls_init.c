#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fd; } ;
struct TYPE_6__ {int sockfd; TYPE_1__ server_fd; scalar_t__ error_handle; } ;
typedef  TYPE_2__ esp_tls_t ;
typedef  int /*<<< orphan*/  esp_tls_last_error_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

esp_tls_t *esp_tls_init(void)
{
    esp_tls_t *tls = (esp_tls_t *)calloc(1, sizeof(esp_tls_t));
    if (!tls) {
        return NULL;
    }
    tls->error_handle = calloc(1, sizeof(esp_tls_last_error_t));
    if (!tls->error_handle) {
        free(tls);
        return NULL;
    }
#ifdef CONFIG_ESP_TLS_USING_MBEDTLS
    tls->server_fd.fd = tls->sockfd = -1;
#endif
    return tls;
}