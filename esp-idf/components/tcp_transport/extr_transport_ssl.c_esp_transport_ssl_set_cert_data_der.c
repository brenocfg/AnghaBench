#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cacert_bytes; void* cacert_buf; } ;
struct TYPE_5__ {TYPE_1__ cfg; } ;
typedef  TYPE_2__ transport_ssl_t ;
typedef  scalar_t__ esp_transport_handle_t ;

/* Variables and functions */
 TYPE_2__* esp_transport_get_context_data (scalar_t__) ; 

void esp_transport_ssl_set_cert_data_der(esp_transport_handle_t t, const char *data, int len)
{
    transport_ssl_t *ssl = esp_transport_get_context_data(t);
    if (t && ssl) {
        ssl->cfg.cacert_buf = (void *)data;
        ssl->cfg.cacert_bytes = len;
    }
}