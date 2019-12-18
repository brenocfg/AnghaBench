#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {TYPE_1__* sd; } ;
struct httpd_req {struct httpd_req_aux* aux; } ;
struct TYPE_2__ {size_t pending_len; scalar_t__ pending_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 size_t MIN (int,size_t) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 

size_t httpd_unrecv(struct httpd_req *r, const char *buf, size_t buf_len)
{
    struct httpd_req_aux *ra = r->aux;
    /* Truncate if external buf_len is greater than pending_data buffer size */
    ra->sd->pending_len = MIN(sizeof(ra->sd->pending_data), buf_len);

    /* Copy data into internal pending_data buffer with the exact offset
     * such that it is right aligned inside the buffer */
    size_t offset = sizeof(ra->sd->pending_data) - ra->sd->pending_len;
    memcpy(ra->sd->pending_data + offset, buf, ra->sd->pending_len);
    ESP_LOGD(TAG, LOG_FMT("length = %d"), ra->sd->pending_len);
    return ra->sd->pending_len;
}