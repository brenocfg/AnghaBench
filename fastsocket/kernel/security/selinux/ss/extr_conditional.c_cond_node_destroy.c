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
struct cond_node {int /*<<< orphan*/  false_list; int /*<<< orphan*/  true_list; struct cond_node* next; struct cond_node* expr; } ;
struct cond_expr {int /*<<< orphan*/  false_list; int /*<<< orphan*/  true_list; struct cond_expr* next; struct cond_expr* expr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_av_list_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cond_node*) ; 

__attribute__((used)) static void cond_node_destroy(struct cond_node *node)
{
	struct cond_expr *cur_expr, *next_expr;

	for (cur_expr = node->expr; cur_expr; cur_expr = next_expr) {
		next_expr = cur_expr->next;
		kfree(cur_expr);
	}
	cond_av_list_destroy(node->true_list);
	cond_av_list_destroy(node->false_list);
	kfree(node);
}