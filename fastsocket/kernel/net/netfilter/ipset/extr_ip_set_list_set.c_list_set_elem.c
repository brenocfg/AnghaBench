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
typedef  int u32 ;
struct set_elem {int dummy; } ;
struct list_set {int dsize; scalar_t__ members; } ;

/* Variables and functions */

__attribute__((used)) static inline struct set_elem *
list_set_elem(const struct list_set *map, u32 id)
{
	return (struct set_elem *)((void *)map->members + id * map->dsize);
}