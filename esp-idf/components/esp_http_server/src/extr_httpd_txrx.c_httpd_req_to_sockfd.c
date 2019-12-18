#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {TYPE_1__* sd; } ;
struct TYPE_6__ {struct httpd_req_aux* aux; } ;
typedef  TYPE_2__ httpd_req_t ;
struct TYPE_5__ {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  httpd_valid_req (TYPE_2__*) ; 

int httpd_req_to_sockfd(httpd_req_t *r)
{
    if (r == NULL) {
        return -1;
    }

    if (!httpd_valid_req(r)) {
        ESP_LOGW(TAG, LOG_FMT("invalid request"));
        return -1;
    }

    struct httpd_req_aux *ra = r->aux;
    return ra->sd->fd;
}