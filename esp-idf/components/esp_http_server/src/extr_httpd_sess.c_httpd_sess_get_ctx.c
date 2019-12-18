#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock_db {void* ctx; } ;
struct TYPE_4__ {void* sess_ctx; } ;
struct TYPE_3__ {struct sock_db* sd; } ;
struct httpd_data {TYPE_2__ hd_req; TYPE_1__ hd_req_aux; } ;
typedef  scalar_t__ httpd_handle_t ;

/* Variables and functions */
 struct sock_db* httpd_sess_get (scalar_t__,int) ; 

void *httpd_sess_get_ctx(httpd_handle_t handle, int sockfd)
{
    struct sock_db *sd = httpd_sess_get(handle, sockfd);
    if (sd == NULL) {
        return NULL;
    }

    /* Check if the function has been called from inside a
     * request handler, in which case fetch the context from
     * the httpd_req_t structure */
    struct httpd_data *hd = (struct httpd_data *) handle;
    if (hd->hd_req_aux.sd == sd) {
        return hd->hd_req.sess_ctx;
    }

    return sd->ctx;
}