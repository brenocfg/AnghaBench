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

__attribute__((used)) static struct node *find(struct node *n, const void *k,
	int (*cmp)(const void *, const void *))
{
	int c;

	if (!n)
		return 0;
	c = cmp(k, n->key);
	if (c == 0)
		return n;
	if (c < 0)
		return find(n->left, k, cmp);
	else
		return find(n->right, k, cmp);
}