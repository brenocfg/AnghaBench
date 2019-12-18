#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* ctx; int /*<<< orphan*/  cmp; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ bintree_t ;
typedef  int /*<<< orphan*/  bintree_cmp_func ;

/* Variables and functions */
 int /*<<< orphan*/  bintree_new_nil_node (int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 

bintree_t *bintree_new(bintree_cmp_func cmp, void *ctx)
{
   bintree_t *t = (bintree_t*)calloc(1, sizeof(*t));

   if (!t)
      return NULL;

   t->root = bintree_new_nil_node(NULL);
   t->cmp  = cmp;
   t->ctx  = ctx;

   return t;
}