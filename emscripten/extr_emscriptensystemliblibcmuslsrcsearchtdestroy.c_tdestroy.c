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
struct node {void* key; void* right; void* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct node*) ; 

void tdestroy(void *root, void (*freekey)(void *))
{
	struct node *r = root;

	if (r == 0)
		return;
	tdestroy(r->left, freekey);
	tdestroy(r->right, freekey);
	if (freekey) freekey(r->key);
	free(r);
}