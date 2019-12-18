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
typedef  int /*<<< orphan*/  symbol_filter_t ;
struct symbol {int dummy; } ;
struct map {int /*<<< orphan*/  type; int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 struct symbol* dso__find_symbol_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dso__sort_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__sorted_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ map__load (struct map*,int /*<<< orphan*/ ) ; 

struct symbol *map__find_symbol_by_name(struct map *self, const char *name,
					symbol_filter_t filter)
{
	if (map__load(self, filter) < 0)
		return NULL;

	if (!dso__sorted_by_name(self->dso, self->type))
		dso__sort_by_name(self->dso, self->type);

	return dso__find_symbol_by_name(self->dso, self->type, name);
}