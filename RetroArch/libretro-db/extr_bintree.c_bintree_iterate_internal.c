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
struct bintree_node {struct bintree_node* right; int /*<<< orphan*/  value; struct bintree_node* left; } ;
typedef  int (* bintree_iter_cb ) (int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 scalar_t__ bintree_is_nil (struct bintree_node*) ; 

__attribute__((used)) static int bintree_iterate_internal(struct bintree_node *n,
      bintree_iter_cb cb, void *ctx)
{
   int rv;

   if (bintree_is_nil(n))
      return 0;

   if ((rv = bintree_iterate_internal(n->left, cb, ctx)) != 0)
      return rv;
   if ((rv = cb(n->value, ctx)) != 0)
      return rv;
   if ((rv = bintree_iterate_internal(n->right, cb, ctx)) != 0)
      return rv;

   return 0;
}