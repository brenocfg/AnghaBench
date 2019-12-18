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
struct net_buf_simple {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUF_SIMPLE_DBG (char*,struct net_buf_simple*,size_t) ; 
 void* memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  net_buf_simple_add (struct net_buf_simple*,size_t) ; 

void *net_buf_simple_add_mem(struct net_buf_simple *buf, const void *mem,
                             size_t len)
{
    NET_BUF_SIMPLE_DBG("buf %p len %u", buf, len);

    return memcpy(net_buf_simple_add(buf, len), mem, len);
}