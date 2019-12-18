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
struct alloc_zone {int dead; struct alloc_zone* next_zone; } ;
struct TYPE_2__ {struct alloc_zone* zones; } ;

/* Variables and functions */
 TYPE_1__ G ; 
 int /*<<< orphan*/  gcc_assert (struct alloc_zone*) ; 

void
destroy_ggc_zone (struct alloc_zone * dead_zone)
{
  struct alloc_zone *z;

  for (z = G.zones; z && z->next_zone != dead_zone; z = z->next_zone)
    /* Just find that zone.  */
    continue;

  /* We should have found the zone in the list.  Anything else is fatal.  */
  gcc_assert (z);

  /* z is dead, baby. z is dead.  */
  z->dead = true;
}