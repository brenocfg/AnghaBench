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
struct TYPE_4__ {int c_id; struct TYPE_4__* c_next; } ;
typedef  TYPE_1__ callout ;

/* Variables and functions */
 TYPE_1__ callouts ; 
 int /*<<< orphan*/  free_callout (TYPE_1__*) ; 

void
untimeout(int id)
{
  callout *cp, *cp2;
  for (cp = &callouts; (cp2 = cp->c_next); cp = cp2) {
    if (cp2->c_id == id) {
      cp->c_next = cp2->c_next;
      free_callout(cp2);
      break;
    }
  }
}