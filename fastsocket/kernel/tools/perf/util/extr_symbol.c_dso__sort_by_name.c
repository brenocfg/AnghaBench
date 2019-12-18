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
struct dso {int /*<<< orphan*/ * symbols; int /*<<< orphan*/ * symbol_names; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 int /*<<< orphan*/  dso__set_sorted_by_name (struct dso*,int) ; 
 void symbols__sort_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dso__sort_by_name(struct dso *dso, enum map_type type)
{
	dso__set_sorted_by_name(dso, type);
	return symbols__sort_by_name(&dso->symbol_names[type],
				     &dso->symbols[type]);
}