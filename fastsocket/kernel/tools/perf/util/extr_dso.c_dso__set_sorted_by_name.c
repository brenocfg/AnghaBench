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
struct dso {int sorted_by_name; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */

void dso__set_sorted_by_name(struct dso *dso, enum map_type type)
{
	dso->sorted_by_name |= (1 << type);
}