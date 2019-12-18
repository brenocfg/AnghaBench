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
struct TYPE_5__ {int pending_len; int (* recv_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fd; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int HTTPD_SOCK_ERR_TIMEOUT ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 size_t httpd_recv_pending (TYPE_2__*,char*,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

int httpd_recv_with_opt(httpd_req_t *r, char *buf, size_t buf_len, bool halt_after_pending)
{
    ESP_LOGD(TAG, LOG_FMT("requested length = %d"), buf_len);

    size_t pending_len = 0;
    struct httpd_req_aux *ra = r->aux;

    /* First fetch pending data from local buffer */
    if (ra->sd->pending_len > 0) {
        ESP_LOGD(TAG, LOG_FMT("pending length = %d"), ra->sd->pending_len);
        pending_len = httpd_recv_pending(r, buf, buf_len);
        buf     += pending_len;
        buf_len -= pending_len;

        /* If buffer filled then no need to recv.
         * If asked to halt after receiving pending data then
         * return with received length */
        if (!buf_len || halt_after_pending) {
            return pending_len;
        }
    }

    /* Receive data of remaining length */
    int ret = ra->sd->recv_fn(ra->sd->handle, ra->sd->fd, buf, buf_len, 0);
    if (ret < 0) {
        ESP_LOGD(TAG, LOG_FMT("error in recv_fn"));
        if ((ret == HTTPD_SOCK_ERR_TIMEOUT) && (pending_len != 0)) {
            /* If recv() timeout occurred, but pending data is
             * present, return length of pending data.
             * This behavior is similar to that of socket recv()
             * function, which, in case has only partially read the
             * requested length, due to timeout, returns with read
             * length, rather than error */
            return pending_len;
        }
        return ret;
    }

    ESP_LOGD(TAG, LOG_FMT("received length = %d"), ret + pending_len);
    return ret + pending_len;
}