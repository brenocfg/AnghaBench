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
struct page_entry {size_t bytes; char* page; unsigned int order; unsigned long context_depth; size_t num_free_objects; int next_bit_hint; unsigned long* in_use_p; TYPE_1__* group; struct page_entry* next; } ;
struct TYPE_4__ {char* allocation; size_t alloc_size; scalar_t__ in_use; struct TYPE_4__* next; } ;
typedef  TYPE_1__ page_group ;
typedef  int /*<<< orphan*/  page_entry ;
struct TYPE_5__ {size_t pagesize; int lg_pagesize; size_t bytes_mapped; unsigned long context_depth; unsigned long context_depth_allocations; int /*<<< orphan*/  debug_file; struct page_entry* free_pages; TYPE_1__* page_groups; } ;

/* Variables and functions */
 size_t BITMAP_SIZE (size_t) ; 
 TYPE_3__ G ; 
 int GGC_DEBUG_LEVEL ; 
 int GGC_QUIRE_SIZE ; 
 size_t HOST_BITS_PER_LONG ; 
 size_t OBJECTS_PER_PAGE (unsigned int) ; 
 size_t OBJECT_SIZE (unsigned int) ; 
 char* alloc_anon (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,void*,unsigned long,char*,char*) ; 
 int /*<<< orphan*/  free (struct page_entry*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  memset (struct page_entry*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_page_group_in_use (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  set_page_table_entry (char*,struct page_entry*) ; 
 struct page_entry* xcalloc (int,size_t) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static inline struct page_entry *
alloc_page (unsigned order)
{
  struct page_entry *entry, *p, **pp;
  char *page;
  size_t num_objects;
  size_t bitmap_size;
  size_t page_entry_size;
  size_t entry_size;
#ifdef USING_MALLOC_PAGE_GROUPS
  page_group *group;
#endif

  num_objects = OBJECTS_PER_PAGE (order);
  bitmap_size = BITMAP_SIZE (num_objects + 1);
  page_entry_size = sizeof (page_entry) - sizeof (long) + bitmap_size;
  entry_size = num_objects * OBJECT_SIZE (order);
  if (entry_size < G.pagesize)
    entry_size = G.pagesize;

  entry = NULL;
  page = NULL;

  /* Check the list of free pages for one we can use.  */
  for (pp = &G.free_pages, p = *pp; p; pp = &p->next, p = *pp)
    if (p->bytes == entry_size)
      break;

  if (p != NULL)
    {
      /* Recycle the allocated memory from this page ...  */
      *pp = p->next;
      page = p->page;

#ifdef USING_MALLOC_PAGE_GROUPS
      group = p->group;
#endif

      /* ... and, if possible, the page entry itself.  */
      if (p->order == order)
	{
	  entry = p;
	  memset (entry, 0, page_entry_size);
	}
      else
	free (p);
    }
#ifdef USING_MMAP
  else if (entry_size == G.pagesize)
    {
      /* We want just one page.  Allocate a bunch of them and put the
	 extras on the freelist.  (Can only do this optimization with
	 mmap for backing store.)  */
      struct page_entry *e, *f = G.free_pages;
      int i;

      page = alloc_anon (NULL, G.pagesize * GGC_QUIRE_SIZE);

      /* This loop counts down so that the chain will be in ascending
	 memory order.  */
      for (i = GGC_QUIRE_SIZE - 1; i >= 1; i--)
	{
	  e = xcalloc (1, page_entry_size);
	  e->order = order;
	  e->bytes = G.pagesize;
	  e->page = page + (i << G.lg_pagesize);
	  e->next = f;
	  f = e;
	}

      G.free_pages = f;
    }
  else
    page = alloc_anon (NULL, entry_size);
#endif
#ifdef USING_MALLOC_PAGE_GROUPS
  else
    {
      /* Allocate a large block of memory and serve out the aligned
	 pages therein.  This results in much less memory wastage
	 than the traditional implementation of valloc.  */

      char *allocation, *a, *enda;
      size_t alloc_size, head_slop, tail_slop;
      int multiple_pages = (entry_size == G.pagesize);

      if (multiple_pages)
	alloc_size = GGC_QUIRE_SIZE * G.pagesize;
      else
	alloc_size = entry_size + G.pagesize - 1;
      allocation = xmalloc (alloc_size);

      page = (char *) (((size_t) allocation + G.pagesize - 1) & -G.pagesize);
      head_slop = page - allocation;
      if (multiple_pages)
	tail_slop = ((size_t) allocation + alloc_size) & (G.pagesize - 1);
      else
	tail_slop = alloc_size - entry_size - head_slop;
      enda = allocation + alloc_size - tail_slop;

      /* We allocated N pages, which are likely not aligned, leaving
	 us with N-1 usable pages.  We plan to place the page_group
	 structure somewhere in the slop.  */
      if (head_slop >= sizeof (page_group))
	group = (page_group *)page - 1;
      else
	{
	  /* We magically got an aligned allocation.  Too bad, we have
	     to waste a page anyway.  */
	  if (tail_slop == 0)
	    {
	      enda -= G.pagesize;
	      tail_slop += G.pagesize;
	    }
	  gcc_assert (tail_slop >= sizeof (page_group));
	  group = (page_group *)enda;
	  tail_slop -= sizeof (page_group);
	}

      /* Remember that we allocated this memory.  */
      group->next = G.page_groups;
      group->allocation = allocation;
      group->alloc_size = alloc_size;
      group->in_use = 0;
      G.page_groups = group;
      G.bytes_mapped += alloc_size;

      /* If we allocated multiple pages, put the rest on the free list.  */
      if (multiple_pages)
	{
	  struct page_entry *e, *f = G.free_pages;
	  for (a = enda - G.pagesize; a != page; a -= G.pagesize)
	    {
	      e = xcalloc (1, page_entry_size);
	      e->order = order;
	      e->bytes = G.pagesize;
	      e->page = a;
	      e->group = group;
	      e->next = f;
	      f = e;
	    }
	  G.free_pages = f;
	}
    }
#endif

  if (entry == NULL)
    entry = xcalloc (1, page_entry_size);

  entry->bytes = entry_size;
  entry->page = page;
  entry->context_depth = G.context_depth;
  entry->order = order;
  entry->num_free_objects = num_objects;
  entry->next_bit_hint = 1;

  G.context_depth_allocations |= (unsigned long)1 << G.context_depth;

#ifdef USING_MALLOC_PAGE_GROUPS
  entry->group = group;
  set_page_group_in_use (group, page);
#endif

  /* Set the one-past-the-end in-use bit.  This acts as a sentry as we
     increment the hint.  */
  entry->in_use_p[num_objects / HOST_BITS_PER_LONG]
    = (unsigned long) 1 << (num_objects % HOST_BITS_PER_LONG);

  set_page_table_entry (page, entry);

  if (GGC_DEBUG_LEVEL >= 2)
    fprintf (G.debug_file,
	     "Allocating page at %p, object size=%lu, data %p-%p\n",
	     (void *) entry, (unsigned long) OBJECT_SIZE (order), page,
	     page + entry_size - 1);

  return entry;
}