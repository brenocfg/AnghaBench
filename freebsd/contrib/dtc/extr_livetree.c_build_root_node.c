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
struct node {int dummy; } ;

/* Variables and functions */
 struct node* build_and_name_child_node (struct node*,char*) ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 struct node* get_subnode (struct node*,char*) ; 

__attribute__((used)) static struct node *build_root_node(struct node *dt, char *name)
{
	struct node *an;

	an = get_subnode(dt, name);
	if (!an)
		an = build_and_name_child_node(dt, name);

	if (!an)
		die("Could not build root node /%s\n", name);

	return an;
}