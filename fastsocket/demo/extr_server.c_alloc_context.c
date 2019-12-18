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
struct context_pool {scalar_t__ allocated; scalar_t__ total; size_t next_idx; struct conn_context* arr; } ;
struct conn_context {size_t next_idx; struct context_pool* pool; scalar_t__ end_fd_added; scalar_t__ end_fd; scalar_t__ fd_added; scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

struct conn_context *alloc_context(struct context_pool *pool)
{
	struct conn_context *ret;

	assert(pool->allocated < pool->total);
	pool->allocated++;

	ret = &pool->arr[pool->next_idx];
	pool->next_idx = pool->arr[pool->next_idx].next_idx;

	ret->fd = 0;
	ret->fd_added = 0;
	ret->end_fd = 0;
	ret->end_fd_added = 0;
	ret->next_idx = -1;

	ret->pool = pool;

	return ret;
}