#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ max; int /*<<< orphan*/  current; int /*<<< orphan*/  store; int /*<<< orphan*/  mark; } ;
typedef  TYPE_1__ store_pool ;
struct TYPE_7__ {scalar_t__ mark; scalar_t__ size; TYPE_1__* pool; } ;
typedef  TYPE_2__ store_memory ;
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  scalar_t__ png_bytep ;
typedef  scalar_t__ png_alloc_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ memcmp (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_pool_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
store_memory_free(png_const_structp pp, store_pool *pool, store_memory *memory)
{
   /* Note that pp may be NULL (see store_pool_delete below), the caller has
    * found 'memory' in pool->list *and* unlinked this entry, so this is a valid
    * pointer (for sure), but the contents may have been trashed.
    */
   if (memory->pool != pool)
      store_pool_error(pool->store, pp, "memory corrupted (pool)");

   else if (memcmp(memory->mark, pool->mark, sizeof memory->mark) != 0)
      store_pool_error(pool->store, pp, "memory corrupted (start)");

   /* It should be safe to read the size field now. */
   else
   {
      png_alloc_size_t cb = memory->size;

      if (cb > pool->max)
         store_pool_error(pool->store, pp, "memory corrupted (size)");

      else if (memcmp((png_bytep)(memory+1)+cb, pool->mark, sizeof pool->mark)
         != 0)
         store_pool_error(pool->store, pp, "memory corrupted (end)");

      /* Finally give the library a chance to find problems too: */
      else
         {
         pool->current -= cb;
         free(memory);
         }
   }
}