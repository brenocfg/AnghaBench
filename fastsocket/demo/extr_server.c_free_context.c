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
struct context_pool {scalar_t__ allocated; int arr; struct conn_context* next_idx; } ;
struct conn_context {struct conn_context* next_idx; struct context_pool* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void free_context(struct conn_context *context)
{
	struct context_pool *pool = context->pool;

	assert(pool->allocated > 0);
	pool->allocated--;

	context->next_idx = pool->next_idx;
	pool->next_idx = context - pool->arr;
}