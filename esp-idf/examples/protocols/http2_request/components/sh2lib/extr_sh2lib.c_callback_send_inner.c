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
typedef  int /*<<< orphan*/  uint8_t ;
struct sh2lib_handle {int /*<<< orphan*/  http2_tls; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ESP_TLS_ERR_SSL_WANT_READ ; 
 int ESP_TLS_ERR_SSL_WANT_WRITE ; 
 int NGHTTP2_ERR_CALLBACK_FAILURE ; 
 int NGHTTP2_ERR_WOULDBLOCK ; 
 int esp_tls_conn_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static ssize_t callback_send_inner(struct sh2lib_handle *hd, const uint8_t *data,
                                   size_t length)
{
    int rv = esp_tls_conn_write(hd->http2_tls, data, length);
    if (rv <= 0) {
        if (rv == ESP_TLS_ERR_SSL_WANT_READ || rv == ESP_TLS_ERR_SSL_WANT_WRITE) {
            rv = NGHTTP2_ERR_WOULDBLOCK;
        } else {
            rv = NGHTTP2_ERR_CALLBACK_FAILURE;
        }
    }
    return rv;
}