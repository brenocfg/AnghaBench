#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ page_start; struct TYPE_4__* next; struct TYPE_4__* previous; int /*<<< orphan*/  original_permissions; scalar_t__ reference_count; } ;
typedef  TYPE_1__ memory_page_t ;
struct TYPE_5__ {int /*<<< orphan*/  page_count; TYPE_1__* buckets; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int get_dictionary_bucket_of_page (scalar_t__) ; 
 TYPE_2__ memory_page_dictionary ; 
 int /*<<< orphan*/  require_memory_page_dictionary () ; 
 int /*<<< orphan*/  write_protect_page (int,scalar_t__) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static memory_page_t *
get_dictionary_entry_of_page (int pid, CORE_ADDR page_start)
{
  int bucket;
  memory_page_t *page = NULL;
  memory_page_t *previous_page = NULL;

  /* We're going to be using the dictionary now, than-kew. */
  require_memory_page_dictionary ();

  /* Try to find an existing dictionary entry for this page.  Hash
     on the page's starting address.
   */
  bucket = get_dictionary_bucket_of_page (page_start);
  page = &memory_page_dictionary.buckets[bucket];
  while (page != NULL)
    {
      if (page->page_start == page_start)
	break;
      previous_page = page;
      page = page->next;
    }

  /* Did we find a dictionary entry for this page?  If not, then
     add it to the dictionary now.
   */
  if (page == NULL)
    {
      /* Create a new entry. */
      page = (memory_page_t *) xmalloc (sizeof (memory_page_t));
      page->page_start = page_start;
      page->reference_count = 0;
      page->next = NULL;
      page->previous = NULL;

      /* We'll write-protect the page now, if that's allowed. */
      page->original_permissions = write_protect_page (pid, page_start);

      /* Add the new entry to the dictionary. */
      page->previous = previous_page;
      previous_page->next = page;

      memory_page_dictionary.page_count++;
    }

  return page;
}