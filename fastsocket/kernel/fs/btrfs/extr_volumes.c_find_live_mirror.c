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
struct map_lookup {TYPE_2__* stripes; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ bdev; } ;

/* Variables and functions */

__attribute__((used)) static int find_live_mirror(struct map_lookup *map, int first, int num,
			    int optimal)
{
	int i;
	if (map->stripes[optimal].dev->bdev)
		return optimal;
	for (i = first; i < first + num; i++) {
		if (map->stripes[i].dev->bdev)
			return i;
	}
	/* we couldn't find one that doesn't fail.  Just return something
	 * and the io error handling code will clean up eventually
	 */
	return optimal;
}