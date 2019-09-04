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
struct TYPE_4__ {scalar_t__ X; scalar_t__* offset; int flags; struct TYPE_4__* link; int /*<<< orphan*/  height; } ;
typedef  TYPE_1__** PProfileList ;
typedef  TYPE_1__* PProfile ;

/* Variables and functions */
 int Flow_Up ; 

__attribute__((used)) static void
  Sort( PProfileList  list )
  {
    PProfile  *old, current, next;


    /* First, set the new X coordinate of each profile */
    current = *list;
    while ( current )
    {
      current->X       = *current->offset;
      current->offset += current->flags & Flow_Up ? 1 : -1;
      current->height--;
      current = current->link;
    }

    /* Then sort them */
    old     = list;
    current = *old;

    if ( !current )
      return;

    next = current->link;

    while ( next )
    {
      if ( current->X <= next->X )
      {
        old     = &current->link;
        current = *old;

        if ( !current )
          return;
      }
      else
      {
        *old          = next;
        current->link = next->link;
        next->link    = current;

        old     = list;
        current = *old;
      }

      next = current->link;
    }
  }