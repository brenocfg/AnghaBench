#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct map_info {unsigned long map_priv_1; } ;

/* Variables and functions */
 unsigned long WINDOW_SHIFT ; 
 int /*<<< orphan*/  __vmax301_page (struct map_info*,unsigned long) ; 

__attribute__((used)) static inline void vmax301_page(struct map_info *map,
				  unsigned long ofs)
{
	unsigned long page = (ofs >> WINDOW_SHIFT);
	if (map->map_priv_1 != page)
		__vmax301_page(map, page);
}