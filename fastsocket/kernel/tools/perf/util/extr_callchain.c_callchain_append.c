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
struct callchain_root {scalar_t__ max_depth; int /*<<< orphan*/  node; } ;
struct callchain_cursor {scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_chain_children (int /*<<< orphan*/ *,struct callchain_cursor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_cursor_commit (struct callchain_cursor*) ; 

int callchain_append(struct callchain_root *root,
		     struct callchain_cursor *cursor,
		     u64 period)
{
	if (!cursor->nr)
		return 0;

	callchain_cursor_commit(cursor);

	append_chain_children(&root->node, cursor, period);

	if (cursor->nr > root->max_depth)
		root->max_depth = cursor->nr;

	return 0;
}