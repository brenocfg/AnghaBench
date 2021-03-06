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
struct map_info {scalar_t__ map_priv_2; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 unsigned long WINDOW_MASK ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmax301_page (struct map_info*,unsigned long) ; 
 int /*<<< orphan*/  vmax301_spin ; 

__attribute__((used)) static map_word vmax301_read8(struct map_info *map, unsigned long ofs)
{
	map_word ret;
	spin_lock(&vmax301_spin);
	vmax301_page(map, ofs);
	ret.x[0] = readb(map->map_priv_2 + (ofs & WINDOW_MASK));
	spin_unlock(&vmax301_spin);
	return ret;
}