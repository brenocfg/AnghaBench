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
typedef  int u32 ;
struct ip_set {int /*<<< orphan*/  family; struct bitmap_ipmac* data; } ;
struct bitmap_ipmac {int dsize; int first_ip; int last_ip; int /*<<< orphan*/  timeout; int /*<<< orphan*/  members; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IPSET_NO_TIMEOUT ; 
 int /*<<< orphan*/  ip_set_alloc (int) ; 

__attribute__((used)) static bool
init_map_ipmac(struct ip_set *set, struct bitmap_ipmac *map,
	       u32 first_ip, u32 last_ip)
{
	map->members = ip_set_alloc((last_ip - first_ip + 1) * map->dsize);
	if (!map->members)
		return false;
	map->first_ip = first_ip;
	map->last_ip = last_ip;
	map->timeout = IPSET_NO_TIMEOUT;

	set->data = map;
	set->family = AF_INET;

	return true;
}