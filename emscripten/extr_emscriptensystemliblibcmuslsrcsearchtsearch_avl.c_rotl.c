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
struct node {struct node* left; struct node* right; } ;

/* Variables and functions */
 int /*<<< orphan*/  updateheight (struct node*) ; 

__attribute__((used)) static struct node *rotl(struct node *n) {
	struct node *r = n->right;
	n->right = r->left;
	r->left = n;
	updateheight(n);
	updateheight(r);
	return r;
}