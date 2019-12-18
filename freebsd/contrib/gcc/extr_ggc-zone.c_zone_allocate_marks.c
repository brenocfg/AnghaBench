#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct small_page_entry {int /*<<< orphan*/ * mark_bits; struct small_page_entry* next; } ;
struct alloc_zone {size_t n_small_pages; struct small_page_entry* pages; int /*<<< orphan*/ * mark_bits; struct alloc_zone* next_zone; } ;
typedef  int /*<<< orphan*/  mark_type ;
struct TYPE_4__ {struct alloc_zone* zones; } ;
struct TYPE_3__ {scalar_t__ bytes; int /*<<< orphan*/ * mark_bits; } ;

/* Variables and functions */
 int BYTES_PER_MARK_WORD ; 
 size_t CEIL (scalar_t__,int) ; 
 TYPE_2__ G ; 
 int GGC_PAGE_SIZE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__ pch_zone ; 
 scalar_t__ xcalloc (int,size_t) ; 

__attribute__((used)) static void
zone_allocate_marks (void)
{
  struct alloc_zone *zone;

  for (zone = G.zones; zone; zone = zone->next_zone)
    {
      struct small_page_entry *page;
      mark_type *cur_marks;
      size_t mark_words, mark_words_per_page;
#ifdef ENABLE_CHECKING
      size_t n = 0;
#endif

      mark_words_per_page
	= (GGC_PAGE_SIZE + BYTES_PER_MARK_WORD - 1) / BYTES_PER_MARK_WORD;
      mark_words = zone->n_small_pages * mark_words_per_page;
      zone->mark_bits = (mark_type *) xcalloc (sizeof (mark_type),
						   mark_words);
      cur_marks = zone->mark_bits;
      for (page = zone->pages; page; page = page->next)
	{
	  page->mark_bits = cur_marks;
	  cur_marks += mark_words_per_page;
#ifdef ENABLE_CHECKING
	  n++;
#endif
	}
#ifdef ENABLE_CHECKING
      gcc_assert (n == zone->n_small_pages);
#endif
    }

  /* We don't collect the PCH zone, but we do have to mark it
     (for now).  */
  if (pch_zone.bytes)
    pch_zone.mark_bits
      = (mark_type *) xcalloc (sizeof (mark_type),
			       CEIL (pch_zone.bytes, BYTES_PER_MARK_WORD));
}