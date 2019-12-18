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
struct ip_set {struct bitmap_ipmac* data; } ;
struct bitmap_ipmac {int last_ip; int first_ip; int dsize; int /*<<< orphan*/  members; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bitmap_ipmac_flush(struct ip_set *set)
{
	struct bitmap_ipmac *map = set->data;

	memset(map->members, 0,
	       (map->last_ip - map->first_ip + 1) * map->dsize);
}