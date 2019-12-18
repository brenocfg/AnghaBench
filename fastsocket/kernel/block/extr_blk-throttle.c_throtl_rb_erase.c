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
struct throtl_rb_root {int /*<<< orphan*/  count; int /*<<< orphan*/  rb; struct rb_node* left; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase_init (struct rb_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void throtl_rb_erase(struct rb_node *n, struct throtl_rb_root *root)
{
	if (root->left == n)
		root->left = NULL;
	rb_erase_init(n, &root->rb);
	--root->count;
}