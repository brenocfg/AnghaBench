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
struct TYPE_2__ {scalar_t__ page_size; scalar_t__ page_protections_allowed; } ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int PROT_WRITE ; 
 int /*<<< orphan*/  TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_GET_MPROTECT ; 
 int /*<<< orphan*/  TT_PROC_SET_MPROTECT ; 
 int call_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 TYPE_1__ memory_page_dictionary ; 

__attribute__((used)) static int
write_protect_page (int pid, CORE_ADDR page_start)
{
  int tt_status;
  int original_permissions;
  int new_permissions;

  tt_status = call_ttrace (TT_PROC_GET_MPROTECT,
			   pid,
			   (TTRACE_ARG_TYPE) page_start,
			   TT_NIL,
			   (TTRACE_ARG_TYPE) & original_permissions);
  if (errno || (tt_status < 0))
    {
      return 0;			/* What else can we do? */
    }

  /* We'll also write-protect the page now, if that's allowed. */
  if (memory_page_dictionary.page_protections_allowed)
    {
      new_permissions = original_permissions & ~PROT_WRITE;
      tt_status = call_ttrace (TT_PROC_SET_MPROTECT,
			       pid,
			       (TTRACE_ARG_TYPE) page_start,
			 (TTRACE_ARG_TYPE) memory_page_dictionary.page_size,
			       (TTRACE_ARG_TYPE) new_permissions);
      if (errno || (tt_status < 0))
	{
	  return 0;		/* What else can we do? */
	}
    }

  return original_permissions;
}