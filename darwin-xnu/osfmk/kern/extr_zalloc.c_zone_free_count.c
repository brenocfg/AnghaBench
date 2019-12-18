#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
typedef  scalar_t__ integer_t ;
struct TYPE_5__ {scalar_t__ countfree; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lock_zone (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_zone (TYPE_1__*) ; 

integer_t
zone_free_count(zone_t zone)
{
	integer_t free_count;

	lock_zone(zone);
	free_count = zone->countfree;
	unlock_zone(zone);

	assert(free_count >= 0);

	return(free_count);
}