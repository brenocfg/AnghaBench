#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  original_permissions; int /*<<< orphan*/  page_start; } ;
typedef  TYPE_2__ memory_page_t ;
struct TYPE_6__ {scalar_t__ page_protections_allowed; TYPE_1__* buckets; } ;
struct TYPE_4__ {TYPE_2__* next; } ;

/* Variables and functions */
 int MEMORY_PAGE_DICTIONARY_BUCKET_COUNT ; 
 TYPE_3__ memory_page_dictionary ; 
 int /*<<< orphan*/  unwrite_protect_page (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
hppa_disable_page_protection_events (int pid)
{
  int bucket;

  for (bucket = 0; bucket < MEMORY_PAGE_DICTIONARY_BUCKET_COUNT; bucket++)
    {
      memory_page_t *page;

      page = memory_page_dictionary.buckets[bucket].next;
      while (page != NULL)
	{
	  unwrite_protect_page (pid, page->page_start, page->original_permissions);
	  page = page->next;
	}
    }

  memory_page_dictionary.page_protections_allowed = 0;
}