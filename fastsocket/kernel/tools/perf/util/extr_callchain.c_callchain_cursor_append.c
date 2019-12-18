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
struct symbol {int dummy; } ;
struct map {int dummy; } ;
struct callchain_cursor_node {struct callchain_cursor_node* next; struct symbol* sym; struct map* map; int /*<<< orphan*/  ip; } ;
struct callchain_cursor {struct callchain_cursor_node** last; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct callchain_cursor_node* calloc (int,int) ; 

int callchain_cursor_append(struct callchain_cursor *cursor,
			    u64 ip, struct map *map, struct symbol *sym)
{
	struct callchain_cursor_node *node = *cursor->last;

	if (!node) {
		node = calloc(sizeof(*node), 1);
		if (!node)
			return -ENOMEM;

		*cursor->last = node;
	}

	node->ip = ip;
	node->map = map;
	node->sym = sym;

	cursor->nr++;

	cursor->last = &node->next;

	return 0;
}