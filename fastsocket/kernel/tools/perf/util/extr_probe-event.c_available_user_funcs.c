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
struct map {int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 int __show_available_funcs (struct map*) ; 
 int /*<<< orphan*/  dso__delete (int /*<<< orphan*/ ) ; 
 struct map* dso__new_map (char const*) ; 
 int init_user_exec () ; 
 int /*<<< orphan*/  map__delete (struct map*) ; 

__attribute__((used)) static int available_user_funcs(const char *target)
{
	struct map *map;
	int ret;

	ret = init_user_exec();
	if (ret < 0)
		return ret;

	map = dso__new_map(target);
	ret = __show_available_funcs(map);
	dso__delete(map->dso);
	map__delete(map);
	return ret;
}