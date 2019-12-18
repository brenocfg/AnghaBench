#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page_entry {TYPE_4__* zone; scalar_t__ pch_p; scalar_t__ large_p; } ;
struct TYPE_7__ {TYPE_2__* zone; } ;
struct large_page_entry {scalar_t__ bytes; TYPE_3__ common; TYPE_1__* prev; struct large_page_entry* next; } ;
struct TYPE_8__ {size_t allocated; } ;
struct TYPE_6__ {int /*<<< orphan*/  allocated; struct large_page_entry* large_pages; } ;
struct TYPE_5__ {struct large_page_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_chunk (void*,size_t,TYPE_4__*) ; 
 int /*<<< orphan*/  free_large_page (struct large_page_entry*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  ggc_free_overhead (void*) ; 
 size_t ggc_get_size (void*) ; 
 int /*<<< orphan*/  poison_region (void*,size_t) ; 
 struct page_entry* zone_get_object_page (void*) ; 

void
ggc_free (void *p)
{
  struct page_entry *page;

#ifdef GATHER_STATISTICS
  ggc_free_overhead (p);
#endif

  poison_region (p, ggc_get_size (p));

  page = zone_get_object_page (p);

  if (page->large_p)
    {
      struct large_page_entry *large_page
	= (struct large_page_entry *) page;

      /* Remove the page from the linked list.  */
      if (large_page->prev)
	large_page->prev->next = large_page->next;
      else
	{
	  gcc_assert (large_page->common.zone->large_pages == large_page);
	  large_page->common.zone->large_pages = large_page->next;
	}
      if (large_page->next)
	large_page->next->prev = large_page->prev;

      large_page->common.zone->allocated -= large_page->bytes;

      /* Release the memory associated with this object.  */
      free_large_page (large_page);
    }
  else if (page->pch_p)
    /* Don't do anything.  We won't allocate a new object from the
       PCH zone so there's no point in releasing anything.  */
    ;
  else
    {
      size_t size = ggc_get_size (p);

      page->zone->allocated -= size;

      /* Add the chunk to the free list.  We don't bother with coalescing,
	 since we are likely to want a chunk of this size again.  */
      free_chunk (p, size, page->zone);
    }
}