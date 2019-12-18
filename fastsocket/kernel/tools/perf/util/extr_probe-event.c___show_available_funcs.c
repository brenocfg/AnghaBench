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
struct map {int /*<<< orphan*/  type; int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dso__fprintf_symbols_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__sort_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__sorted_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_available_functions ; 
 scalar_t__ map__load (struct map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int __show_available_funcs(struct map *map)
{
	if (map__load(map, filter_available_functions)) {
		pr_err("Failed to load map.\n");
		return -EINVAL;
	}
	if (!dso__sorted_by_name(map->dso, map->type))
		dso__sort_by_name(map->dso, map->type);

	dso__fprintf_symbols_by_name(map->dso, map->type, stdout);
	return 0;
}