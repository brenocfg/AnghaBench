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
typedef  size_t u32 ;
struct set_elem {int /*<<< orphan*/  id; } ;
struct list_set {size_t size; size_t dsize; unsigned long timeout; } ;
struct ip_set {struct list_set* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPSET_INVALID_ID ; 
 struct list_set* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct set_elem* list_set_elem (struct list_set*,size_t) ; 

__attribute__((used)) static bool
init_list_set(struct ip_set *set, u32 size, size_t dsize,
	      unsigned long timeout)
{
	struct list_set *map;
	struct set_elem *e;
	u32 i;

	map = kzalloc(sizeof(*map) + size * dsize, GFP_KERNEL);
	if (!map)
		return false;

	map->size = size;
	map->dsize = dsize;
	map->timeout = timeout;
	set->data = map;

	for (i = 0; i < size; i++) {
		e = list_set_elem(map, i);
		e->id = IPSET_INVALID_ID;
	}

	return true;
}