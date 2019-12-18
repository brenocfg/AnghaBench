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
typedef  size_t u16_t ;
struct net_buf_pool {size_t buf_count; struct net_buf* __bufs; } ;
struct net_buf {struct net_buf_pool* pool; } ;

/* Variables and functions */

__attribute__((used)) static inline struct net_buf *pool_get_uninit(struct net_buf_pool *pool,
        u16_t uninit_count)
{
    struct net_buf *buf;

    buf = &pool->__bufs[pool->buf_count - uninit_count];

    buf->pool = pool;

    return buf;
}