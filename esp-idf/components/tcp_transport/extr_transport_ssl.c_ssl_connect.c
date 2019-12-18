#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int timeout_ms; } ;
struct TYPE_7__ {int ssl_initialized; TYPE_3__* tls; TYPE_4__ cfg; } ;
typedef  TYPE_1__ transport_ssl_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  error_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_tls_conn_delete (TYPE_3__*) ; 
 scalar_t__ esp_tls_conn_new_sync (char const*,int /*<<< orphan*/ ,int,TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* esp_tls_init () ; 
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_set_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int ssl_connect(esp_transport_handle_t t, const char *host, int port, int timeout_ms)
{
    transport_ssl_t *ssl = esp_transport_get_context_data(t);

    ssl->cfg.timeout_ms = timeout_ms;
    ssl->ssl_initialized = true;
    ssl->tls = esp_tls_init();
    if (esp_tls_conn_new_sync(host, strlen(host), port, &ssl->cfg, ssl->tls) < 0) {
        ESP_LOGE(TAG, "Failed to open a new connection");
        esp_transport_set_errors(t, ssl->tls->error_handle);
        esp_tls_conn_delete(ssl->tls);
        ssl->tls = NULL;
        return -1;
    }

    return 0;
}