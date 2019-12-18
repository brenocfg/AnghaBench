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
typedef  scalar_t__ u_int ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  opaque_t ;
typedef  int /*<<< orphan*/  callout_fun ;
struct TYPE_4__ {scalar_t__ c_time; int c_id; struct TYPE_4__* c_next; int /*<<< orphan*/ * c_fn; int /*<<< orphan*/  c_arg; } ;
typedef  TYPE_1__ callout ;

/* Variables and functions */
 int CID_ALLOC () ; 
 TYPE_1__* alloc_callout () ; 
 TYPE_1__ callouts ; 
 scalar_t__ clocktime (int /*<<< orphan*/ *) ; 
 scalar_t__ next_softclock ; 

int
timeout(u_int secs, callout_fun *fn, opaque_t fn_arg)
{
  callout *cp, *cp2;
  time_t t = clocktime(NULL) + secs;

  /*
   * Allocate and fill in a new callout structure
   */
  callout *cpnew = alloc_callout();
  cpnew->c_arg = fn_arg;
  cpnew->c_fn = fn;
  cpnew->c_time = t;
  cpnew->c_id = CID_ALLOC();

  if (t < next_softclock)
    next_softclock = t;

  /*
   * Find the correct place in the list
   */
  for (cp = &callouts; (cp2 = cp->c_next); cp = cp2)
    if (cp2->c_time >= t)
      break;

  /*
   * And link it in
   */
  cp->c_next = cpnew;
  cpnew->c_next = cp2;

  /*
   * Return callout identifier
   */
  return cpnew->c_id;
}