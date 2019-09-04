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
struct node {void const* key; struct node* right; struct node* left; } ;

/* Variables and functions */
 struct node* balance (struct node*) ; 
 int /*<<< orphan*/  free (struct node*) ; 
 struct node* remove_rightmost (struct node*,struct node**) ; 

__attribute__((used)) static struct node *remove(struct node **n, const void *k,
	int (*cmp)(const void *, const void *), struct node *parent)
{
	int c;

	if (!*n)
		return 0;
	c = cmp(k, (*n)->key);
	if (c == 0) {
		struct node *r = *n;
		if (r->left) {
			r->left = remove_rightmost(r->left, n);
			(*n)->left = r->left;
			(*n)->right = r->right;
			*n = balance(*n);
		} else
			*n = r->right;
		free(r);
		return parent;
	}
	if (c < 0)
		parent = remove(&(*n)->left, k, cmp, *n);
	else
		parent = remove(&(*n)->right, k, cmp, *n);
	if (parent)
		*n = balance(*n);
	return parent;
}