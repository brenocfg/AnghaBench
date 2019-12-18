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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  symbol_filter_t ;
struct symbol {int dummy; } ;
struct map_groups {int dummy; } ;
struct map {int /*<<< orphan*/  (* map_ip ) (struct map*,int /*<<< orphan*/ ) ;} ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 struct symbol* map__find_symbol (struct map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct map* map_groups__find (struct map_groups*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct map*,int /*<<< orphan*/ ) ; 

struct symbol *map_groups__find_symbol(struct map_groups *mg,
				       enum map_type type, u64 addr,
				       struct map **mapp,
				       symbol_filter_t filter)
{
	struct map *map = map_groups__find(mg, type, addr);

	if (map != NULL) {
		if (mapp != NULL)
			*mapp = map;
		return map__find_symbol(map, map->map_ip(map, addr), filter);
	}

	return NULL;
}