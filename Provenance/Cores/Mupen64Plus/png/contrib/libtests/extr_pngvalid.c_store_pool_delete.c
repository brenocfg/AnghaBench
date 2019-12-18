#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ max; scalar_t__ max_max; scalar_t__ current; scalar_t__ limit; scalar_t__ max_limit; scalar_t__ total; scalar_t__ max_total; int /*<<< orphan*/  mark; TYPE_3__* list; } ;
typedef  TYPE_2__ store_pool ;
struct TYPE_11__ {scalar_t__ size; struct TYPE_11__* next; } ;
typedef  TYPE_3__ store_memory ;
struct TYPE_12__ {char* test; char* wname; TYPE_1__* current; TYPE_2__ read_memory_pool; int /*<<< orphan*/  nerrors; } ;
typedef  TYPE_4__ png_store ;
struct TYPE_9__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  store_memory_free (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  store_pool_mark (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_pool_delete(png_store *ps, store_pool *pool)
{
   if (pool->list != NULL)
   {
      fprintf(stderr, "%s: %s %s: memory lost (list follows):\n", ps->test,
         pool == &ps->read_memory_pool ? "read" : "write",
         pool == &ps->read_memory_pool ? (ps->current != NULL ?
            ps->current->name : "unknown file") : ps->wname);
      ++ps->nerrors;

      do
      {
         store_memory *next = pool->list;
         pool->list = next->next;
         next->next = NULL;

         fprintf(stderr, "\t%lu bytes @ %p\n",
             (unsigned long)next->size, (const void*)(next+1));
         /* The NULL means this will always return, even if the memory is
          * corrupted.
          */
         store_memory_free(NULL, pool, next);
      }
      while (pool->list != NULL);
   }

   /* And reset the other fields too for the next time. */
   if (pool->max > pool->max_max) pool->max_max = pool->max;
   pool->max = 0;
   if (pool->current != 0) /* unexpected internal error */
      fprintf(stderr, "%s: %s %s: memory counter mismatch (internal error)\n",
         ps->test, pool == &ps->read_memory_pool ? "read" : "write",
         pool == &ps->read_memory_pool ? (ps->current != NULL ?
            ps->current->name : "unknown file") : ps->wname);
   pool->current = 0;

   if (pool->limit > pool->max_limit)
      pool->max_limit = pool->limit;

   pool->limit = 0;

   if (pool->total > pool->max_total)
      pool->max_total = pool->total;

   pool->total = 0;

   /* Get a new mark too. */
   store_pool_mark(pool->mark);
}