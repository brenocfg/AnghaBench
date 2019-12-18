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
struct pevent {int func_count; struct func_list* funclist; struct func_map* func_map; } ;
struct func_map {int /*<<< orphan*/ * mod; scalar_t__ addr; int /*<<< orphan*/ * func; } ;
struct func_list {struct func_list* next; int /*<<< orphan*/ * mod; scalar_t__ addr; int /*<<< orphan*/ * func; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct func_list*) ; 
 int /*<<< orphan*/  func_cmp ; 
 struct func_map* malloc (int) ; 
 int /*<<< orphan*/  qsort (struct func_map*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int func_map_init(struct pevent *pevent)
{
	struct func_list *funclist;
	struct func_list *item;
	struct func_map *func_map;
	int i;

	func_map = malloc(sizeof(*func_map) * (pevent->func_count + 1));
	if (!func_map)
		return -1;

	funclist = pevent->funclist;

	i = 0;
	while (funclist) {
		func_map[i].func = funclist->func;
		func_map[i].addr = funclist->addr;
		func_map[i].mod = funclist->mod;
		i++;
		item = funclist;
		funclist = funclist->next;
		free(item);
	}

	qsort(func_map, pevent->func_count, sizeof(*func_map), func_cmp);

	/*
	 * Add a special record at the end.
	 */
	func_map[pevent->func_count].func = NULL;
	func_map[pevent->func_count].addr = 0;
	func_map[pevent->func_count].mod = NULL;

	pevent->func_map = func_map;
	pevent->funclist = NULL;

	return 0;
}