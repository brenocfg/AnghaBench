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
struct node {scalar_t__ phandle; } ;
typedef  int cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_property (struct node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  build_property (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  data_append_cell (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  empty_data ; 
 scalar_t__ get_node_by_phandle (struct node*,int) ; 
 int /*<<< orphan*/  get_property (struct node*,char*) ; 

cell_t get_node_phandle(struct node *root, struct node *node)
{
	static cell_t phandle = 1; /* FIXME: ick, static local */

	if ((node->phandle != 0) && (node->phandle != -1))
		return node->phandle;

	assert(! get_property(node, "linux,phandle"));

	while (get_node_by_phandle(root, phandle))
		phandle++;

	node->phandle = phandle;
	add_property(node,
		     build_property("linux,phandle",
				    data_append_cell(empty_data, phandle),
				    NULL));

	return node->phandle;
}