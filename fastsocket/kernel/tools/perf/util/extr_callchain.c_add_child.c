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
struct callchain_node {int /*<<< orphan*/  hit; scalar_t__ children_hit; } ;
struct callchain_cursor {int dummy; } ;

/* Variables and functions */
 struct callchain_node* create_child (struct callchain_node*,int) ; 
 int /*<<< orphan*/  fill_node (struct callchain_node*,struct callchain_cursor*) ; 

__attribute__((used)) static void
add_child(struct callchain_node *parent,
	  struct callchain_cursor *cursor,
	  u64 period)
{
	struct callchain_node *new;

	new = create_child(parent, false);
	fill_node(new, cursor);

	new->children_hit = 0;
	new->hit = period;
}