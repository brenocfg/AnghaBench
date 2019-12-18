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
struct net_buf {int /*<<< orphan*/  ref; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUF_ASSERT (struct net_buf*) ; 
 int /*<<< orphan*/  NET_BUF_DBG (char*,struct net_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct net_buf *net_buf_ref(struct net_buf *buf)
{
    NET_BUF_ASSERT(buf);

    NET_BUF_DBG("buf %p (old) ref %u pool %p", buf, buf->ref, buf->pool);

    buf->ref++;
    return buf;
}