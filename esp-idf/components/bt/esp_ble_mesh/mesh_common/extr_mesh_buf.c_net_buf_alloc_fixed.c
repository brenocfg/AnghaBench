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
struct net_buf_pool_fixed {int /*<<< orphan*/  data_size; } ;
struct net_buf_pool {TYPE_1__* alloc; } ;
struct net_buf {int dummy; } ;
typedef  int /*<<< orphan*/  s32_t ;
struct TYPE_2__ {struct net_buf_pool_fixed* alloc_data; } ;

/* Variables and functions */
 struct net_buf* net_buf_alloc_len (struct net_buf_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct net_buf *net_buf_alloc_fixed(struct net_buf_pool *pool, s32_t timeout)
{
    const struct net_buf_pool_fixed *fixed = pool->alloc->alloc_data;

    return net_buf_alloc_len(pool, fixed->data_size, timeout);
}