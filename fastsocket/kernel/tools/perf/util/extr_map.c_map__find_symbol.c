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
struct map {int /*<<< orphan*/  type; int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 struct symbol* dso__find_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ map__load (struct map*,int /*<<< orphan*/ ) ; 

struct symbol *map__find_symbol(struct map *self, u64 addr,
				symbol_filter_t filter)
{
	if (map__load(self, filter) < 0)
		return NULL;

	return dso__find_symbol(self->dso, self->type, addr);
}