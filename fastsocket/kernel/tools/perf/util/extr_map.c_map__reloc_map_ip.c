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
typedef  scalar_t__ u64 ;
struct map {scalar_t__ pgoff; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */

__attribute__((used)) static u64 map__reloc_map_ip(struct map *map, u64 ip)
{
	return ip + (s64)map->pgoff;
}