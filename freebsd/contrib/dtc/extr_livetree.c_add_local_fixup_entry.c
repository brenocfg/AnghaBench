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
typedef  int /*<<< orphan*/  value_32 ;
typedef  int /*<<< orphan*/  uint32_t ;
struct property {int /*<<< orphan*/  name; } ;
struct node {char* name; struct node* parent; } ;
struct marker {int /*<<< orphan*/  offset; } ;
struct dt_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_to_property (struct node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct node* build_and_name_child_node (struct node*,char*) ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char**) ; 
 struct node* get_subnode (struct node*,char*) ; 
 char** xmalloc (int) ; 

__attribute__((used)) static void add_local_fixup_entry(struct dt_info *dti,
		struct node *lfn, struct node *node,
		struct property *prop, struct marker *m,
		struct node *refnode)
{
	struct node *wn, *nwn;	/* local fixup node, walk node, new */
	uint32_t value_32;
	char **compp;
	int i, depth;

	/* walk back retreiving depth */
	depth = 0;
	for (wn = node; wn; wn = wn->parent)
		depth++;

	/* allocate name array */
	compp = xmalloc(sizeof(*compp) * depth);

	/* store names in the array */
	for (wn = node, i = depth - 1; wn; wn = wn->parent, i--)
		compp[i] = wn->name;

	/* walk the path components creating nodes if they don't exist */
	for (wn = lfn, i = 1; i < depth; i++, wn = nwn) {
		/* if no node exists, create it */
		nwn = get_subnode(wn, compp[i]);
		if (!nwn)
			nwn = build_and_name_child_node(wn, compp[i]);
	}

	free(compp);

	value_32 = cpu_to_fdt32(m->offset);
	append_to_property(wn, prop->name, &value_32, sizeof(value_32));
}