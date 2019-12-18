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
typedef  int /*<<< orphan*/  httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_tls_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int esp_tls_conn_write (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * httpd_sess_get_transport_ctx (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int httpd_ssl_send(httpd_handle_t server, int sockfd, const char *buf, size_t buf_len, int flags)
{
    esp_tls_t *tls = httpd_sess_get_transport_ctx(server, sockfd);
    assert(tls != NULL);
    return esp_tls_conn_write(tls, buf, buf_len);
}