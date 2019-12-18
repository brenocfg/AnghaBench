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
struct TYPE_2__ {int len; } ;
struct property {TYPE_1__ val; } ;
struct node {int phandle; int /*<<< orphan*/  fullpath; } ;
struct check {int dummy; } ;
typedef  int cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (struct check*,char*,int /*<<< orphan*/ ,int,...) ; 
 struct node* get_node_by_phandle (struct node*,int) ; 
 struct property* get_property (struct node*,char*) ; 
 int propval_cell (struct property*) ; 

__attribute__((used)) static void check_explicit_phandles(struct check *c, struct node *root,
					  struct node *node)
{
	struct property *prop;
	struct node *other;
	cell_t phandle;

	prop = get_property(node, "linux,phandle");
	if (! prop)
		return; /* No phandle, that's fine */

	if (prop->val.len != sizeof(cell_t)) {
		FAIL(c, "%s has bad length (%d) linux,phandle property",
		     node->fullpath, prop->val.len);
		return;
	}

	phandle = propval_cell(prop);
	if ((phandle == 0) || (phandle == -1)) {
		FAIL(c, "%s has invalid linux,phandle value 0x%x",
		     node->fullpath, phandle);
		return;
	}

	other = get_node_by_phandle(root, phandle);
	if (other) {
		FAIL(c, "%s has duplicated phandle 0x%x (seen before at %s)",
		     node->fullpath, phandle, other->fullpath);
		return;
	}

	node->phandle = phandle;
}