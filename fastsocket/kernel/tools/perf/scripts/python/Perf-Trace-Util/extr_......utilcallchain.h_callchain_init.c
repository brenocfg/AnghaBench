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
struct TYPE_2__ {scalar_t__ children_hit; scalar_t__ hit; int /*<<< orphan*/ * parent; int /*<<< orphan*/  val; int /*<<< orphan*/  children; int /*<<< orphan*/  siblings; } ;
struct callchain_root {scalar_t__ max_depth; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void callchain_init(struct callchain_root *root)
{
	INIT_LIST_HEAD(&root->node.siblings);
	INIT_LIST_HEAD(&root->node.children);
	INIT_LIST_HEAD(&root->node.val);

	root->node.parent = NULL;
	root->node.hit = 0;
	root->node.children_hit = 0;
	root->max_depth = 0;
}