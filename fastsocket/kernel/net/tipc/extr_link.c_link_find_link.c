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
struct tipc_node {struct link** links; } ;
struct link_name {int /*<<< orphan*/  addr_peer; int /*<<< orphan*/  if_local; } ;
struct link {int /*<<< orphan*/  name; } ;
struct bearer {size_t identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  link_name_validate (char const*,struct link_name*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct bearer* tipc_bearer_find_interface (int /*<<< orphan*/ ) ; 
 struct tipc_node* tipc_node_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct link *link_find_link(const char *name, struct tipc_node **node)
{
	struct link_name link_name_parts;
	struct bearer *b_ptr;
	struct link *l_ptr;

	if (!link_name_validate(name, &link_name_parts))
		return NULL;

	b_ptr = tipc_bearer_find_interface(link_name_parts.if_local);
	if (!b_ptr)
		return NULL;

	*node = tipc_node_find(link_name_parts.addr_peer);
	if (!*node)
		return NULL;

	l_ptr = (*node)->links[b_ptr->identity];
	if (!l_ptr || strcmp(l_ptr->name, name))
		return NULL;

	return l_ptr;
}