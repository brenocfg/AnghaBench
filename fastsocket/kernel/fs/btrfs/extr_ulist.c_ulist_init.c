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
struct ulist {int /*<<< orphan*/  nodes_alloced; int /*<<< orphan*/  int_nodes; int /*<<< orphan*/  nodes; scalar_t__ nnodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULIST_SIZE ; 

void ulist_init(struct ulist *ulist)
{
	ulist->nnodes = 0;
	ulist->nodes = ulist->int_nodes;
	ulist->nodes_alloced = ULIST_SIZE;
}