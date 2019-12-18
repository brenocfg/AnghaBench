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
struct sock_db {void* transport_ctx; int /*<<< orphan*/  free_transport_ctx; } ;
typedef  int /*<<< orphan*/  httpd_handle_t ;
typedef  int /*<<< orphan*/  httpd_free_ctx_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  httpd_sess_free_ctx (void*,int /*<<< orphan*/ ) ; 
 struct sock_db* httpd_sess_get (int /*<<< orphan*/ ,int) ; 

void httpd_sess_set_transport_ctx(httpd_handle_t handle, int sockfd, void *ctx, httpd_free_ctx_fn_t free_fn)
{
    struct sock_db *sd = httpd_sess_get(handle, sockfd);
    if (sd == NULL) {
        return;
    }

    if (sd->transport_ctx != ctx) {
        /* Free previous transport context */
        httpd_sess_free_ctx(sd->transport_ctx, sd->free_transport_ctx);
        sd->transport_ctx = ctx;
    }
    sd->free_transport_ctx = free_fn;
}