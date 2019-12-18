#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pid; int tid; struct TYPE_4__* next; struct TYPE_4__* thread_list; } ;
typedef  TYPE_1__ procinfo ;

/* Variables and functions */
 TYPE_1__* procinfo_list ; 

__attribute__((used)) static procinfo *
find_procinfo (int pid, int tid)
{
  procinfo *pi;

  for (pi = procinfo_list; pi; pi = pi->next)
    if (pi->pid == pid)
      break;

  if (pi)
    if (tid)
      {
	/* Don't check threads_valid.  If we're updating the
	   thread_list, we want to find whatever threads are already
	   here.  This means that in general it is the caller's
	   responsibility to check threads_valid and update before
	   calling find_procinfo, if the caller wants to find a new
	   thread. */

	for (pi = pi->thread_list; pi; pi = pi->next)
	  if (pi->tid == tid)
	    break;
      }

  return pi;
}