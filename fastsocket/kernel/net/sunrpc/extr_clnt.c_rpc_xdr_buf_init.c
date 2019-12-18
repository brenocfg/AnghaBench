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
struct xdr_buf {size_t buflen; scalar_t__ len; scalar_t__ flags; scalar_t__ page_len; TYPE_1__* tail; TYPE_2__* head; } ;
struct TYPE_4__ {size_t iov_len; void* iov_base; } ;
struct TYPE_3__ {scalar_t__ iov_len; } ;

/* Variables and functions */

__attribute__((used)) static inline void
rpc_xdr_buf_init(struct xdr_buf *buf, void *start, size_t len)
{
	buf->head[0].iov_base = start;
	buf->head[0].iov_len = len;
	buf->tail[0].iov_len = 0;
	buf->page_len = 0;
	buf->flags = 0;
	buf->len = 0;
	buf->buflen = len;
}