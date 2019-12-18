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
struct net_buf_simple {size_t data; size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUF_SIMPLE_ASSERT (int) ; 
 int /*<<< orphan*/  NET_BUF_SIMPLE_DBG (char*,struct net_buf_simple*,size_t) ; 
 size_t net_buf_simple_headroom (struct net_buf_simple*) ; 

void *net_buf_simple_push(struct net_buf_simple *buf, size_t len)
{
    NET_BUF_SIMPLE_DBG("buf %p len %u", buf, len);

    NET_BUF_SIMPLE_ASSERT(net_buf_simple_headroom(buf) >= len);

    buf->data -= len;
    buf->len += len;
    return buf->data;
}