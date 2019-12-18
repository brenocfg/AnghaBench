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
struct TYPE_3__ {int ssl_initialized; int /*<<< orphan*/  tls; } ;
typedef  TYPE_1__ transport_ssl_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_tls_conn_delete (int /*<<< orphan*/ ) ; 
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_close(esp_transport_handle_t t)
{
    int ret = -1;
    transport_ssl_t *ssl = esp_transport_get_context_data(t);
    if (ssl->ssl_initialized) {
        esp_tls_conn_delete(ssl->tls);
        ssl->ssl_initialized = false;
    }
    return ret;
}