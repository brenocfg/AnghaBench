#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ page_start; TYPE_2__* previous; TYPE_1__* next; int /*<<< orphan*/  original_permissions; } ;
typedef  TYPE_3__ memory_page_t ;
struct TYPE_10__ {int /*<<< orphan*/  page_count; } ;
struct TYPE_8__ {TYPE_1__* next; } ;
struct TYPE_7__ {TYPE_2__* previous; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 TYPE_6__ memory_page_dictionary ; 
 int /*<<< orphan*/  unwrite_protect_page (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (TYPE_3__*) ; 

__attribute__((used)) static void
remove_dictionary_entry_of_page (int pid, memory_page_t *page)
{
  /* Restore the page's original permissions. */
  unwrite_protect_page (pid, page->page_start, page->original_permissions);

  /* Kick the page out of the dictionary. */
  if (page->previous != NULL)
    page->previous->next = page->next;
  if (page->next != NULL)
    page->next->previous = page->previous;

  /* Just in case someone retains a handle to this after it's freed. */
  page->page_start = (CORE_ADDR) 0;

  memory_page_dictionary.page_count--;

  xfree (page);
}