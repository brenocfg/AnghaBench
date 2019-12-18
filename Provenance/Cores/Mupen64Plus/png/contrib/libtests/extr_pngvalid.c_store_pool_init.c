#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mark; scalar_t__ max_total; scalar_t__ max_limit; scalar_t__ max_max; scalar_t__ total; scalar_t__ limit; scalar_t__ current; scalar_t__ max; int /*<<< orphan*/ * list; int /*<<< orphan*/ * store; } ;
typedef  TYPE_1__ store_pool ;
typedef  int /*<<< orphan*/  png_store ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_pool_mark (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_pool_init(png_store *ps, store_pool *pool)
{
   memset(pool, 0, sizeof *pool);

   pool->store = ps;
   pool->list = NULL;
   pool->max = pool->current = pool->limit = pool->total = 0;
   pool->max_max = pool->max_limit = pool->max_total = 0;
   store_pool_mark(pool->mark);
}