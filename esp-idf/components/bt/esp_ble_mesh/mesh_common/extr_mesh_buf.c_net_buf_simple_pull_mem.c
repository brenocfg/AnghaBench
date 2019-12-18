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
struct net_buf_simple {size_t len; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUF_SIMPLE_ASSERT (int) ; 
 int /*<<< orphan*/  NET_BUF_SIMPLE_DBG (char*,struct net_buf_simple*,size_t) ; 

void *net_buf_simple_pull_mem(struct net_buf_simple *buf, size_t len)
{
    void *data = buf->data;

    NET_BUF_SIMPLE_DBG("buf %p len %zu", buf, len);

    NET_BUF_SIMPLE_ASSERT(buf->len >= len);

    buf->len -= len;
    buf->data += len;

    return data;
}