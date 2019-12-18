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
 int esp_tls_get_bytes_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * httpd_sess_get_transport_ctx (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int httpd_ssl_pending(httpd_handle_t server, int sockfd)
{
    esp_tls_t *tls = httpd_sess_get_transport_ctx(server, sockfd);
    assert(tls != NULL);
    return esp_tls_get_bytes_avail(tls);
}