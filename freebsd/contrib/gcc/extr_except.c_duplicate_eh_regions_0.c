#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* eh_region ;
struct TYPE_3__ {int region_number; struct TYPE_3__* next_peer; struct TYPE_3__* inner; } ;

/* Variables and functions */

__attribute__((used)) static void
duplicate_eh_regions_0 (eh_region o, int *min, int *max)
{
  if (o->region_number < *min)
    *min = o->region_number;
  if (o->region_number > *max)
    *max = o->region_number;

  if (o->inner)
    {
      o = o->inner;
      duplicate_eh_regions_0 (o, min, max);
      while (o->next_peer)
	{
	  o = o->next_peer;
	  duplicate_eh_regions_0 (o, min, max);
	}
    }
}