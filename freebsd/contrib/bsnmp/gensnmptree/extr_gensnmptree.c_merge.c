#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  subs; } ;
struct TYPE_4__ {TYPE_1__ tree; } ;
struct node {scalar_t__ type; scalar_t__ id; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ NODE_TREE ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  merge_subs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
merge(struct node **root, struct node *t)
{

	if (*root == NULL) {
		*root = t;
		return;
	}
	if (t == NULL)
		return;

	/* both must be trees */
	if ((*root)->type != NODE_TREE)
		errx(1, "root is not a tree");
	if (t->type != NODE_TREE)
		errx(1, "can merge only with tree");
	if ((*root)->id != t->id)
		errx(1, "trees to merge must have same id");

	merge_subs(&(*root)->u.tree.subs, &t->u.tree.subs);
}