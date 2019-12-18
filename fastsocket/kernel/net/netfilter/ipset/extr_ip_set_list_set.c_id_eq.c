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
typedef  scalar_t__ u32 ;
struct set_elem {scalar_t__ id; } ;
struct list_set {scalar_t__ size; } ;
typedef  scalar_t__ ip_set_id_t ;

/* Variables and functions */
 struct set_elem* list_set_elem (struct list_set const*,scalar_t__) ; 

__attribute__((used)) static bool
id_eq(const struct list_set *map, u32 i, ip_set_id_t id)
{
	const struct set_elem *elem;

	if (i < map->size) {
		elem = list_set_elem(map, i);
		return elem->id == id;
	}

	return 0;
}