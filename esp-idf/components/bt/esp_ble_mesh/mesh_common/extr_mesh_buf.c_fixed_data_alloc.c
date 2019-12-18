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
typedef  int /*<<< orphan*/  u8_t ;
struct net_buf_pool_fixed {int data_size; int /*<<< orphan*/ * data_pool; } ;
struct net_buf_pool {TYPE_1__* alloc; } ;
struct net_buf {struct net_buf_pool* pool; } ;
typedef  int /*<<< orphan*/  s32_t ;
struct TYPE_2__ {struct net_buf_pool_fixed* alloc_data; } ;

/* Variables and functions */
 size_t MIN (int,size_t) ; 
 int net_buf_id (struct net_buf*) ; 

__attribute__((used)) static u8_t *fixed_data_alloc(struct net_buf *buf, size_t *size, s32_t timeout)
{
    struct net_buf_pool *pool = buf->pool;
    const struct net_buf_pool_fixed *fixed = pool->alloc->alloc_data;

    *size = MIN(fixed->data_size, *size);

    return fixed->data_pool + fixed->data_size * net_buf_id(buf);
}