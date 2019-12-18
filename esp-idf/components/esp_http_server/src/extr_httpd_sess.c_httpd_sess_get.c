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
struct sock_db {int fd; } ;
struct TYPE_4__ {int max_open_sockets; } ;
struct TYPE_3__ {struct sock_db* sd; } ;
struct httpd_data {struct sock_db* hd_sd; TYPE_2__ config; TYPE_1__ hd_req_aux; } ;

/* Variables and functions */

struct sock_db *httpd_sess_get(struct httpd_data *hd, int sockfd)
{
    if (hd == NULL) {
        return NULL;
    }

    /* Check if called inside a request handler, and the
     * session sockfd in use is same as the parameter */
    if ((hd->hd_req_aux.sd) && (hd->hd_req_aux.sd->fd == sockfd)) {
        /* Just return the pointer to the sock_db
         * corresponding to the request */
        return hd->hd_req_aux.sd;
    }

    int i;
    for (i = 0; i < hd->config.max_open_sockets; i++) {
        if (hd->hd_sd[i].fd == sockfd) {
            return &hd->hd_sd[i];
        }
    }
    return NULL;
}