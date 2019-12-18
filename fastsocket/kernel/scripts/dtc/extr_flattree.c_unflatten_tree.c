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
typedef  int uint32_t ;
struct property {int dummy; } ;
struct node {char* name; int /*<<< orphan*/  children; } ;
struct inbuf {int dummy; } ;

/* Variables and functions */
#define  FDT_BEGIN_NODE 132 
#define  FDT_END 131 
#define  FDT_END_NODE 130 
#define  FDT_NOP 129 
#define  FDT_PROP 128 
 int FTF_FULLPATH ; 
 int FTF_NOPS ; 
 int /*<<< orphan*/  add_child (struct node*,struct node*) ; 
 int /*<<< orphan*/  add_property (struct node*,struct property*) ; 
 struct node* build_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 struct property* flat_read_property (struct inbuf*,struct inbuf*,int) ; 
 char* flat_read_string (struct inbuf*) ; 
 int flat_read_word (struct inbuf*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* nodename_from_path (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct node *unflatten_tree(struct inbuf *dtbuf,
				   struct inbuf *strbuf,
				   const char *parent_flatname, int flags)
{
	struct node *node;
	char *flatname;
	uint32_t val;

	node = build_node(NULL, NULL);

	flatname = flat_read_string(dtbuf);

	if (flags & FTF_FULLPATH)
		node->name = nodename_from_path(parent_flatname, flatname);
	else
		node->name = flatname;

	do {
		struct property *prop;
		struct node *child;

		val = flat_read_word(dtbuf);
		switch (val) {
		case FDT_PROP:
			if (node->children)
				fprintf(stderr, "Warning: Flat tree input has "
					"subnodes preceding a property.\n");
			prop = flat_read_property(dtbuf, strbuf, flags);
			add_property(node, prop);
			break;

		case FDT_BEGIN_NODE:
			child = unflatten_tree(dtbuf,strbuf, flatname, flags);
			add_child(node, child);
			break;

		case FDT_END_NODE:
			break;

		case FDT_END:
			die("Premature FDT_END in device tree blob\n");
			break;

		case FDT_NOP:
			if (!(flags & FTF_NOPS))
				fprintf(stderr, "Warning: NOP tag found in flat tree"
					" version <16\n");

			/* Ignore */
			break;

		default:
			die("Invalid opcode word %08x in device tree blob\n",
			    val);
		}
	} while (val != FDT_END_NODE);

	return node;
}