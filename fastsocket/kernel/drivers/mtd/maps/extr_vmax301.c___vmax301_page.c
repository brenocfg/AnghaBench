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
struct map_info {unsigned long map_priv_1; scalar_t__ map_priv_2; } ;

/* Variables and functions */
 scalar_t__ WINDOW_LENGTH ; 
 int /*<<< orphan*/  writew (unsigned long,scalar_t__) ; 

__attribute__((used)) static void __vmax301_page(struct map_info *map, unsigned long page)
{
	writew(page, map->map_priv_2 - WINDOW_LENGTH);
	map->map_priv_1 = page;
}