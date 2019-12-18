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
struct page_entry {int context_depth; size_t bytes; char* page; unsigned int order; int* in_use_p; struct page_entry* next; scalar_t__ num_free_objects; } ;
struct ggc_pch_ondisk {size_t* totals; } ;
typedef  struct page_entry page_entry ;
typedef  int /*<<< orphan*/  d ;
struct TYPE_2__ {unsigned long by_depth_in_use; int context_depth; int allocated; int allocated_last_gc; struct page_entry** page_tails; struct page_entry** pages; int /*<<< orphan*/  pagesize; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BITMAP_SIZE (size_t) ; 
 TYPE_1__ G ; 
 size_t HOST_BITS_PER_LONG ; 
 unsigned int NUM_ORDERS ; 
 size_t OBJECT_SIZE (unsigned int) ; 
 size_t ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_marks () ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int fread (struct ggc_pch_ondisk*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  move_ptes_to_front (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  poison_pages () ; 
 int /*<<< orphan*/  push_by_depth (struct page_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_table_entry (char*,struct page_entry*) ; 
 struct page_entry* xcalloc (int,scalar_t__) ; 

void
ggc_pch_read (FILE *f, void *addr)
{
  struct ggc_pch_ondisk d;
  unsigned i;
  char *offs = addr;
  unsigned long count_old_page_tables;
  unsigned long count_new_page_tables;

  count_old_page_tables = G.by_depth_in_use;

  /* We've just read in a PCH file.  So, every object that used to be
     allocated is now free.  */
  clear_marks ();
#ifdef ENABLE_GC_CHECKING
  poison_pages ();
#endif

  /* No object read from a PCH file should ever be freed.  So, set the
     context depth to 1, and set the depth of all the currently-allocated
     pages to be 1 too.  PCH pages will have depth 0.  */
  gcc_assert (!G.context_depth);
  G.context_depth = 1;
  for (i = 0; i < NUM_ORDERS; i++)
    {
      page_entry *p;
      for (p = G.pages[i]; p != NULL; p = p->next)
	p->context_depth = G.context_depth;
    }

  /* Allocate the appropriate page-table entries for the pages read from
     the PCH file.  */
  if (fread (&d, sizeof (d), 1, f) != 1)
    fatal_error ("can't read PCH file: %m");

  for (i = 0; i < NUM_ORDERS; i++)
    {
      struct page_entry *entry;
      char *pte;
      size_t bytes;
      size_t num_objs;
      size_t j;

      if (d.totals[i] == 0)
	continue;

      bytes = ROUND_UP (d.totals[i] * OBJECT_SIZE (i), G.pagesize);
      num_objs = bytes / OBJECT_SIZE (i);
      entry = xcalloc (1, (sizeof (struct page_entry)
			   - sizeof (long)
			   + BITMAP_SIZE (num_objs + 1)));
      entry->bytes = bytes;
      entry->page = offs;
      entry->context_depth = 0;
      offs += bytes;
      entry->num_free_objects = 0;
      entry->order = i;

      for (j = 0;
	   j + HOST_BITS_PER_LONG <= num_objs + 1;
	   j += HOST_BITS_PER_LONG)
	entry->in_use_p[j / HOST_BITS_PER_LONG] = -1;
      for (; j < num_objs + 1; j++)
	entry->in_use_p[j / HOST_BITS_PER_LONG]
	  |= 1L << (j % HOST_BITS_PER_LONG);

      for (pte = entry->page;
	   pte < entry->page + entry->bytes;
	   pte += G.pagesize)
	set_page_table_entry (pte, entry);

      if (G.page_tails[i] != NULL)
	G.page_tails[i]->next = entry;
      else
	G.pages[i] = entry;
      G.page_tails[i] = entry;

      /* We start off by just adding all the new information to the
	 end of the varrays, later, we will move the new information
	 to the front of the varrays, as the PCH page tables are at
	 context 0.  */
      push_by_depth (entry, 0);
    }

  /* Now, we update the various data structures that speed page table
     handling.  */
  count_new_page_tables = G.by_depth_in_use - count_old_page_tables;

  move_ptes_to_front (count_old_page_tables, count_new_page_tables);

  /* Update the statistics.  */
  G.allocated = G.allocated_last_gc = offs - (char *)addr;
}