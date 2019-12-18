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
struct alloc_zone {char const* name; struct alloc_zone* next_zone; } ;
struct TYPE_4__ {TYPE_1__* zones; } ;
struct TYPE_3__ {struct alloc_zone* next_zone; } ;

/* Variables and functions */
 TYPE_2__ G ; 

__attribute__((used)) static void
new_ggc_zone_1 (struct alloc_zone *new_zone, const char * name)
{
  new_zone->name = name;
  new_zone->next_zone = G.zones->next_zone;
  G.zones->next_zone = new_zone;
}