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
struct sh2lib_handle {int /*<<< orphan*/ * hostname; int /*<<< orphan*/ * http2_tls; int /*<<< orphan*/ * http2_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  esp_tls_conn_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nghttp2_session_del (int /*<<< orphan*/ *) ; 

void sh2lib_free(struct sh2lib_handle *hd)
{
    if (hd->http2_sess) {
        nghttp2_session_del(hd->http2_sess);
        hd->http2_sess = NULL;
    }
    if (hd->http2_tls) {
	esp_tls_conn_delete(hd->http2_tls);
        hd->http2_tls = NULL;
    }
    if (hd->hostname) {
        free(hd->hostname);
        hd->hostname = NULL;
    }
}