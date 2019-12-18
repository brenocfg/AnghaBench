#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {TYPE_1__* sd; } ;
struct TYPE_5__ {struct httpd_req_aux* aux; } ;
typedef  TYPE_2__ httpd_req_t ;
struct TYPE_4__ {int pending_len; scalar_t__ pending_data; } ;

/* Variables and functions */
 size_t MIN (int,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 

__attribute__((used)) static size_t httpd_recv_pending(httpd_req_t *r, char *buf, size_t buf_len)
{
    struct httpd_req_aux *ra = r->aux;
    size_t offset = sizeof(ra->sd->pending_data) - ra->sd->pending_len;

    /* buf_len must not be greater than remaining_len */
    buf_len = MIN(ra->sd->pending_len, buf_len);
    memcpy(buf, ra->sd->pending_data + offset, buf_len);

    ra->sd->pending_len -= buf_len;
    return buf_len;
}