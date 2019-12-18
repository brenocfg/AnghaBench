#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  server_fd; scalar_t__ is_tls; } ;
typedef  TYPE_1__ esp_tls_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_mbedtls_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_net_free (int /*<<< orphan*/ *) ; 

void esp_mbedtls_conn_delete(esp_tls_t *tls)
{
    if (tls != NULL) {
        esp_mbedtls_cleanup(tls);
        if (tls->is_tls) {
            mbedtls_net_free(&tls->server_fd);
        }
    }
}