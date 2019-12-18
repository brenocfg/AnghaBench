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
struct sock_db {void* transport_ctx; } ;
typedef  int /*<<< orphan*/  httpd_handle_t ;

/* Variables and functions */
 struct sock_db* httpd_sess_get (int /*<<< orphan*/ ,int) ; 

void *httpd_sess_get_transport_ctx(httpd_handle_t handle, int sockfd)
{
    struct sock_db *sd = httpd_sess_get(handle, sockfd);
    if (sd == NULL) {
        return NULL;
    }

    return sd->transport_ctx;
}