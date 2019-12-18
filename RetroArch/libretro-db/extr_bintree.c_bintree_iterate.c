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
struct TYPE_3__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ bintree_t ;
typedef  int /*<<< orphan*/  bintree_iter_cb ;

/* Variables and functions */
 int bintree_iterate_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int bintree_iterate(const bintree_t *t, bintree_iter_cb cb,
      void *ctx)
{
   return bintree_iterate_internal(t->root, cb, ctx);
}