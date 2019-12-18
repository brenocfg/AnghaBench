#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {scalar_t__ scratch; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {struct httpd_req_aux* aux; } ;
typedef  TYPE_1__ httpd_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  HTTPD_408_REQ_TIMEOUT ; 
 int HTTPD_SOCK_ERR_FAIL ; 
 int HTTPD_SOCK_ERR_TIMEOUT ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 scalar_t__ MIN (size_t,int) ; 
 int /*<<< orphan*/  TAG ; 
 int httpd_recv_with_opt (TYPE_1__*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ httpd_req_handle_err (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_block(httpd_req_t *req, size_t offset, size_t length)
{
    struct httpd_req_aux *raux  = req->aux;

    /* Limits the read to scratch buffer size */
    ssize_t buf_len = MIN(length, (sizeof(raux->scratch) - offset));
    if (buf_len <= 0) {
        return 0;
    }

    /* Receive data into buffer. If data is pending (from unrecv) then return
     * immediately after receiving pending data, as pending data may just complete
     * this request packet. */
    int nbytes = httpd_recv_with_opt(req, raux->scratch + offset, buf_len, true);
    if (nbytes < 0) {
        ESP_LOGD(TAG, LOG_FMT("error in httpd_recv"));
        /* If timeout occurred allow the
         * situation to be handled */
        if (nbytes == HTTPD_SOCK_ERR_TIMEOUT) {
            /* Invoke error handler which may return ESP_OK
             * to signal for retrying call to recv(), else it may
             * return ESP_FAIL to signal for closure of socket */
            return (httpd_req_handle_err(req, HTTPD_408_REQ_TIMEOUT) == ESP_OK) ?
                    HTTPD_SOCK_ERR_TIMEOUT : HTTPD_SOCK_ERR_FAIL;
        }
        /* Some socket error occurred. Return failure
         * to force closure of underlying socket.
         * Error message is not sent as socket may not
         * be valid anymore */
        return HTTPD_SOCK_ERR_FAIL;
    } else if (nbytes == 0) {
        ESP_LOGD(TAG, LOG_FMT("connection closed"));
        /* Connection closed by client so no
         * need to send error response */
        return HTTPD_SOCK_ERR_FAIL;
    }

    ESP_LOGD(TAG, LOG_FMT("received HTTP request block size = %d"), nbytes);
    return nbytes;
}