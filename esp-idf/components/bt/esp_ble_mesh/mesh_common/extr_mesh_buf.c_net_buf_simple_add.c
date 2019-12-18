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
typedef  void u8_t ;
struct net_buf_simple {size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUF_SIMPLE_ASSERT (int) ; 
 int /*<<< orphan*/  NET_BUF_SIMPLE_DBG (char*,struct net_buf_simple*,size_t) ; 
 void* net_buf_simple_tail (struct net_buf_simple*) ; 
 size_t net_buf_simple_tailroom (struct net_buf_simple*) ; 

void *net_buf_simple_add(struct net_buf_simple *buf, size_t len)
{
    u8_t *tail = net_buf_simple_tail(buf);

    NET_BUF_SIMPLE_DBG("buf %p len %u", buf, len);

    NET_BUF_SIMPLE_ASSERT(net_buf_simple_tailroom(buf) >= len);

    buf->len += len;
    return tail;
}