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
struct node {void const* key; int height; struct node* right; struct node* left; } ;

/* Variables and functions */
 struct node* balance (struct node*) ; 
 struct node* malloc (int) ; 

__attribute__((used)) static struct node *insert(struct node *n, const void *k,
	int (*cmp)(const void *, const void *), struct node **found)
{
	struct node *r;
	int c;

	if (!n) {
		n = malloc(sizeof *n);
		if (n) {
			n->key = k;
			n->left = n->right = 0;
			n->height = 1;
		}
		*found = n;
		return n;
	}
	c = cmp(k, n->key);
	if (c == 0) {
		*found = n;
		return 0;
	}
	r = insert(c < 0 ? n->left : n->right, k, cmp, found);
	if (r) {
		if (c < 0)
			n->left = r;
		else
			n->right = r;
		r = balance(n);
	}
	return r;
}