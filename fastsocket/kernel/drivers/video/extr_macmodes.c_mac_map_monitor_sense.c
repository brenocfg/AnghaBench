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
struct monitor_map {int sense; int vmode; } ;

/* Variables and functions */
 struct monitor_map* mac_monitors ; 

int mac_map_monitor_sense(int sense)
{
    const struct monitor_map *map;

    for (map = mac_monitors; map->sense != -1; map++)
	if (map->sense == sense)
	    break;
    return map->vmode;
}