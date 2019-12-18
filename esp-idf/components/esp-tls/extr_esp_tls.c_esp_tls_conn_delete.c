#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sockfd; struct TYPE_5__* error_handle; } ;
typedef  TYPE_1__ esp_tls_t ;

/* Variables and functions */
 int /*<<< orphan*/  _esp_tls_conn_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void esp_tls_conn_delete(esp_tls_t *tls)
{
    if (tls != NULL) {
        _esp_tls_conn_delete(tls);
        if (tls->sockfd >= 0) {
            close(tls->sockfd);
        }
    free(tls->error_handle);
    free(tls);
    }
}