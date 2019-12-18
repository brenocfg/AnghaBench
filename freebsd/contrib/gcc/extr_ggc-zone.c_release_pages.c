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
struct TYPE_2__ {char* page; } ;
struct small_page_entry {TYPE_1__ common; struct small_page_entry* next; } ;
struct alloc_zone {size_t bytes_mapped; struct small_page_entry* free_pages; } ;

/* Variables and functions */
 size_t SMALL_PAGE_SIZE ; 
 int /*<<< orphan*/  munmap (char*,size_t) ; 
 int /*<<< orphan*/  set_page_table_entry (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
release_pages (struct alloc_zone *zone)
{
#ifdef USING_MMAP
  struct small_page_entry *p, *next;
  char *start;
  size_t len;

  /* Gather up adjacent pages so they are unmapped together.  */
  p = zone->free_pages;

  while (p)
    {
      start = p->common.page;
      next = p->next;
      len = SMALL_PAGE_SIZE;
      set_page_table_entry (p->common.page, NULL);
      p = next;

      while (p && p->common.page == start + len)
	{
	  next = p->next;
	  len += SMALL_PAGE_SIZE;
	  set_page_table_entry (p->common.page, NULL);
	  p = next;
	}

      munmap (start, len);
      zone->bytes_mapped -= len;
    }

  zone->free_pages = NULL;
#endif
}