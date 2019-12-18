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
struct TYPE_4__ {int /*<<< orphan*/  reference_count; } ;
typedef  TYPE_1__ memory_page_t ;
struct TYPE_5__ {scalar_t__ page_count; int page_size; } ;
typedef  scalar_t__ LONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 TYPE_1__* get_dictionary_entry_of_page (int,int) ; 
 int /*<<< orphan*/  hppa_enable_syscall_events (int) ; 
 TYPE_2__ memory_page_dictionary ; 
 int /*<<< orphan*/  require_memory_page_dictionary () ; 

int
hppa_insert_hw_watchpoint (int pid, CORE_ADDR start, LONGEST len, int type)
{
  CORE_ADDR page_start;
  int dictionary_was_empty;
  int page_size;
  int page_id;
  LONGEST range_size_in_pages;

  if (type != 0)
    error ("read or access hardware watchpoints not supported on HP-UX");

  /* Examine all pages in the address range. */
  require_memory_page_dictionary ();

  dictionary_was_empty = (memory_page_dictionary.page_count == (LONGEST) 0);

  page_size = memory_page_dictionary.page_size;
  page_start = (start / page_size) * page_size;
  range_size_in_pages = ((LONGEST) len + (LONGEST) page_size - 1) / (LONGEST) page_size;

  for (page_id = 0; page_id < range_size_in_pages; page_id++, page_start += page_size)
    {
      memory_page_t *page;

      /* This gets the page entered into the dictionary if it was
         not already entered.
       */
      page = get_dictionary_entry_of_page (pid, page_start);
      page->reference_count++;
    }

  /* Our implementation depends on seeing calls to kernel code, for the
     following reason.  Here we ask to be notified of syscalls.

     When a protected page is accessed by user code, HP-UX raises a SIGBUS.
     Fine.

     But when kernel code accesses the page, it doesn't give a SIGBUS.
     Rather, the system call that touched the page fails, with errno=EFAULT.
     Not good for us.

     We could accomodate this "feature" by asking to be notified of syscall
     entries & exits; upon getting an entry event, disabling page-protections;
     upon getting an exit event, reenabling page-protections and then checking
     if any watchpoints triggered.

     However, this turns out to be a real performance loser.  syscalls are
     usually a frequent occurrence.  Having to unprotect-reprotect all watched
     pages, and also to then read all watched memory locations and compare for
     triggers, can be quite expensive.

     Instead, we'll only ask to be notified of syscall exits.  When we get
     one, we'll check whether errno is set.  If not, or if it's not EFAULT,
     we can just continue the inferior.

     If errno is set upon syscall exit to EFAULT, we must perform some fairly
     hackish stuff to determine whether the failure really was due to a
     page-protect trap on a watched location.
   */
  if (dictionary_was_empty)
    hppa_enable_syscall_events (pid);

  return 1;
}