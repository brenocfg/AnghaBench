#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* saved_exitset; struct TYPE_7__* saved_entryset; struct TYPE_7__* next; } ;
typedef  TYPE_1__ procinfo ;

/* Variables and functions */
 int /*<<< orphan*/  close_procinfo_files (TYPE_1__*) ; 
 int /*<<< orphan*/  free_syscalls (TYPE_1__*) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static void
destroy_one_procinfo (procinfo **list, procinfo *pi)
{
  procinfo *ptr;

  /* Step one: unlink the procinfo from its list */
  if (pi == *list)
    *list = pi->next;
  else
    for (ptr = *list; ptr; ptr = ptr->next)
      if (ptr->next == pi)
	{
	  ptr->next =  pi->next;
	  break;
	}

  /* Step two: close any open file descriptors */
  close_procinfo_files (pi);

  /* Step three: free the memory. */
#ifdef DYNAMIC_SYSCALLS
  free_syscalls (pi);
#endif
  xfree (pi->saved_entryset);
  xfree (pi->saved_exitset);
  xfree (pi);
}