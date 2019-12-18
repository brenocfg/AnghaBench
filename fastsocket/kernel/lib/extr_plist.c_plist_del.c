#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  node_list; int /*<<< orphan*/  prio_list; } ;
struct plist_node {TYPE_1__ plist; } ;
struct plist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_check_head (struct plist_head*) ; 
 struct plist_node* plist_first (TYPE_1__*) ; 

void plist_del(struct plist_node *node, struct plist_head *head)
{
	plist_check_head(head);

	if (!list_empty(&node->plist.prio_list)) {
		struct plist_node *next = plist_first(&node->plist);

		list_move_tail(&next->plist.prio_list, &node->plist.prio_list);
		list_del_init(&node->plist.prio_list);
	}

	list_del_init(&node->plist.node_list);

	plist_check_head(head);
}