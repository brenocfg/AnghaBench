#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int index_by_depth; scalar_t__ context_depth; struct TYPE_4__* next; scalar_t__ page; int /*<<< orphan*/  group; scalar_t__ bytes; } ;
typedef  TYPE_1__ page_entry ;
struct TYPE_5__ {int by_depth_in_use; TYPE_1__* free_pages; int /*<<< orphan*/ * save_in_use; TYPE_1__** by_depth; int /*<<< orphan*/  debug_file; } ;

/* Variables and functions */
 TYPE_3__ G ; 
 int GGC_DEBUG_LEVEL ; 
 int /*<<< orphan*/  VALGRIND_DISCARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_NOACCESS (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  adjust_depth () ; 
 int /*<<< orphan*/  clear_page_group_in_use (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  set_page_table_entry (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_page (page_entry *entry)
{
  if (GGC_DEBUG_LEVEL >= 2)
    fprintf (G.debug_file,
	     "Deallocating page at %p, data %p-%p\n", (void *) entry,
	     entry->page, entry->page + entry->bytes - 1);

  /* Mark the page as inaccessible.  Discard the handle to avoid handle
     leak.  */
  VALGRIND_DISCARD (VALGRIND_MAKE_NOACCESS (entry->page, entry->bytes));

  set_page_table_entry (entry->page, NULL);

#ifdef USING_MALLOC_PAGE_GROUPS
  clear_page_group_in_use (entry->group, entry->page);
#endif

  if (G.by_depth_in_use > 1)
    {
      page_entry *top = G.by_depth[G.by_depth_in_use-1];
      int i = entry->index_by_depth;

      /* We cannot free a page from a context deeper than the current
	 one.  */
      gcc_assert (entry->context_depth == top->context_depth);
      
      /* Put top element into freed slot.  */
      G.by_depth[i] = top;
      G.save_in_use[i] = G.save_in_use[G.by_depth_in_use-1];
      top->index_by_depth = i;
    }
  --G.by_depth_in_use;

  adjust_depth ();

  entry->next = G.free_pages;
  G.free_pages = entry;
}