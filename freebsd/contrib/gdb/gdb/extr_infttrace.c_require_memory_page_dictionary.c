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
struct TYPE_4__ {scalar_t__ page_count; TYPE_1__* buckets; } ;
struct TYPE_3__ {int /*<<< orphan*/ * previous; int /*<<< orphan*/ * next; scalar_t__ reference_count; scalar_t__ page_start; } ;
typedef  scalar_t__ LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int MEMORY_PAGE_DICTIONARY_BUCKET_COUNT ; 
 TYPE_2__ memory_page_dictionary ; 

__attribute__((used)) static void
require_memory_page_dictionary (void)
{
  int i;

  /* Is the memory page dictionary ready for use?  If so, we're done. */
  if (memory_page_dictionary.page_count >= (LONGEST) 0)
    return;

  /* Else, initialize it. */
  memory_page_dictionary.page_count = (LONGEST) 0;

  for (i = 0; i < MEMORY_PAGE_DICTIONARY_BUCKET_COUNT; i++)
    {
      memory_page_dictionary.buckets[i].page_start = (CORE_ADDR) 0;
      memory_page_dictionary.buckets[i].reference_count = 0;
      memory_page_dictionary.buckets[i].next = NULL;
      memory_page_dictionary.buckets[i].previous = NULL;
    }
}