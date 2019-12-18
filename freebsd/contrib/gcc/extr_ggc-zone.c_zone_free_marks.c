#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct alloc_zone {int /*<<< orphan*/ * mark_bits; struct alloc_zone* next_zone; } ;
struct TYPE_4__ {struct alloc_zone* zones; } ;
struct TYPE_3__ {int /*<<< orphan*/ * mark_bits; scalar_t__ bytes; } ;

/* Variables and functions */
 TYPE_2__ G ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__ pch_zone ; 

__attribute__((used)) static void
zone_free_marks (void)
{
  struct alloc_zone *zone;

  for (zone = G.zones; zone; zone = zone->next_zone)
    if (zone->mark_bits)
      {
	free (zone->mark_bits);
	zone->mark_bits = NULL;
      }

  if (pch_zone.bytes)
    {
      free (pch_zone.mark_bits);
      pch_zone.mark_bits = NULL;
    }
}