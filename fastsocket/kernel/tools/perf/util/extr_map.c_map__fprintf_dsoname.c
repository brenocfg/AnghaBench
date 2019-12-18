#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct map {TYPE_1__* dso; } ;
struct TYPE_4__ {scalar_t__ show_kernel_path; } ;
struct TYPE_3__ {char* name; char* long_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 TYPE_2__ symbol_conf ; 

size_t map__fprintf_dsoname(struct map *map, FILE *fp)
{
	const char *dsoname = "[unknown]";

	if (map && map->dso && (map->dso->name || map->dso->long_name)) {
		if (symbol_conf.show_kernel_path && map->dso->long_name)
			dsoname = map->dso->long_name;
		else if (map->dso->name)
			dsoname = map->dso->name;
	}

	return fprintf(fp, "%s", dsoname);
}