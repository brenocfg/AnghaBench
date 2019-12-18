#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;
typedef  int LONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_GET_MPROTECT ; 
 int /*<<< orphan*/  _SC_PAGE_SIZE ; 
 int call_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int sysconf (int /*<<< orphan*/ ) ; 

int
hppa_range_profitable_for_hw_watchpoint (int pid, CORE_ADDR start, LONGEST len)
{
  int range_is_stack_based;
  int range_is_accessible;
  CORE_ADDR page_start;
  int page_size;
  int page;
  LONGEST range_size_in_pages;

  /* ??rehrauer: For now, say that all addresses are potentially
     profitable.  Possibly later we'll want to test the address
     for "stackness"?
   */
  range_is_stack_based = 0;

  /* If any page in the range is inaccessible, then we cannot
     really use hardware watchpointing, even though our client
     thinks we can.  In that case, it's actually an error to
     attempt to use hw watchpoints, so we'll tell our client
     that the range is "unprofitable", and hope that they listen...
   */
  range_is_accessible = 1;	/* Until proven otherwise. */

  /* Examine all pages in the address range. */
  errno = 0;
  page_size = sysconf (_SC_PAGE_SIZE);

  /* If we can't determine page size, we're hosed.  Tell our
     client it's unprofitable to use hw watchpoints for this
     range.
   */
  if (errno || (page_size <= 0))
    {
      errno = 0;
      return 0;
    }

  page_start = (start / page_size) * page_size;
  range_size_in_pages = len / (LONGEST) page_size;

  for (page = 0; page < range_size_in_pages; page++, page_start += page_size)
    {
      int tt_status;
      int page_permissions;

      /* Is this page accessible? */
      errno = 0;
      tt_status = call_ttrace (TT_PROC_GET_MPROTECT,
			       pid,
			       (TTRACE_ARG_TYPE) page_start,
			       TT_NIL,
			       (TTRACE_ARG_TYPE) & page_permissions);
      if (errno || (tt_status < 0))
	{
	  errno = 0;
	  range_is_accessible = 0;
	  break;
	}

      /* Yes, go for another... */
    }

  return (!range_is_stack_based && range_is_accessible);
}