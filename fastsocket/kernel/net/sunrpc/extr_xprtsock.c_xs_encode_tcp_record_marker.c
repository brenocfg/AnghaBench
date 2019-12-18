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
typedef  int u32 ;
struct xdr_buf {int len; TYPE_1__* head; } ;
typedef  int /*<<< orphan*/  rpc_fraghdr ;
struct TYPE_2__ {int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 int RPC_LAST_STREAM_FRAGMENT ; 
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static inline void xs_encode_tcp_record_marker(struct xdr_buf *buf)
{
	u32 reclen = buf->len - sizeof(rpc_fraghdr);
	rpc_fraghdr *base = buf->head[0].iov_base;
	*base = htonl(RPC_LAST_STREAM_FRAGMENT | reclen);
}